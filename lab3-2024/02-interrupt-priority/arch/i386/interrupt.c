/*! Interrupt handling - 'arch' layer (only basic operations) */

#define _ARCH_INTERRUPTS_C_
#include "interrupt.h"

#include <arch/processor.h>
#include <kernel/errno.h>
#include <lib/list.h>
#include <kernel/memory.h>

/*! Interrupt controller device */
extern arch_ic_t IC_DEV;
static arch_ic_t *icdev = &IC_DEV;

/*! interrupt handlers */
static list_t ihandlers[INTERRUPTS];
static list_t irq_requests;
int irq_prio = 0; //set in drivers/uart.c:uart_read when 1-9 is pressed

struct ihndlr
{
	void *device;
	int (*ihandler)(unsigned int, void *device);
	int irq_num;
	int prio; // prio = irq_num (or MAX for hardware interrupts)

	list_h list;
};

struct irq
{
	struct ihndlr *ihndlr;
	int started;

	list_h list;
};

/*! Initialize interrupt susubsystem (in 'arch' layer) */
void arch_init_interrupts()
{
	int i;

	icdev->init();

	for (i = 0; i < INTERRUPTS; i++)
		list_init(&ihandlers[i]);
	list_init(&irq_requests);
}

/*!
 * enable and disable interrupts generated outside processor, controller by
 * interrupt controller (PIC or APIC or ...)
 */
void arch_irq_enable(unsigned int irq)
{
	icdev->enable_irq(irq);
}
void arch_irq_disable(unsigned int irq)
{
	icdev->disable_irq(irq);
}

/*! Register handler function for particular interrupt number */
void arch_register_interrupt_handler(unsigned int inum, void *handler,
				       void *device)
{
	struct ihndlr *ih;

	if (inum < INTERRUPTS)
	{
		ih = kmalloc(sizeof(struct ihndlr));
		ASSERT(ih);

		ih->device = device;
		ih->ihandler = handler;
		ih->irq_num = inum;
		ih->prio = (inum < SOFT_IRQ ? INTERRUPTS + 1 : inum);

		list_append(&ihandlers[inum], ih, &ih->list);
	}
	else {
		LOG(ERROR, "Interrupt %d can't be used!\n", inum);
		halt();
	}
}

/*! Unregister handler function for particular interrupt number */
void arch_unregister_interrupt_handler(unsigned int irq_num, void *handler,
					 void *device)
{
	struct ihndlr *ih, *next;

	ASSERT(irq_num >= 0 && irq_num < INTERRUPTS);

	ih = list_get(&ihandlers[irq_num], FIRST);

	while (ih)
	{
		next = list_get_next(&ih->list);

		if (ih->ihandler == handler && ih->device == device)
			list_remove(&ihandlers[irq_num], FIRST, &ih->list);

		ih = next;
	}
}

static int prio_cmp(void *a, void *b) {
	struct irq *A = a, *B = b;
	return B->ihndlr->prio - A->ihndlr->prio;
}
static void add_requests(int irq_num)
{
	struct ihndlr *ih = list_get(&ihandlers[irq_num], FIRST);

	while (ih) {
		struct irq *irq = kmalloc(sizeof(struct irq));
		irq->ihndlr = ih;
		irq->started = FALSE;
		list_sort_add(&irq_requests, irq, &irq->list, prio_cmp);

		ih = list_get_next(&ih->list);
	}
}

/*!
 * "Forward" interrupt handling to registered handler
 * (called from interrupts.S)
 */
void arch_interrupt_handler(int irq_num)
{
	struct ihndlr *ih;

	if (irq_num < INTERRUPTS && (ih = list_get(&ihandlers[irq_num], FIRST)))
	{
		/* enable interrupts on PIC immediately since program may not
		 * return here immediately */
		if (icdev->at_exit)
			icdev->at_exit(irq_num);

		add_requests(irq_num);

		struct irq *first = list_get(&irq_requests, FIRST);
		while (first && first->started == FALSE)
		{
			first->started = TRUE;

			arch_enable_interrupts();
			first->ihndlr->ihandler(first->ihndlr->irq_num, first->ihndlr->device);
			arch_disable_interrupts();

			list_remove(&irq_requests, 0, &first->list);
			kfree(first);

			//simulating requests if irq_prio is set (in uart on keystrokes 1-9)
			if (irq_prio > 0) {
				add_requests(SOFT_IRQ + irq_prio % (SIM_INTERRUPTS + 1));
				kprintf("added simulated interrupt %d to queue\n", irq_prio);
				irq_prio = 0;
			}
			first = list_get(&irq_requests, FIRST);
		}
	}

	else if (irq_num < INTERRUPTS)
	{
		LOG(ERROR, "Unregistered interrupt: %d - %s!\n",
		      irq_num, icdev->int_descr(irq_num));
		halt();
	}
	else {
		LOG(ERROR, "Unregistered interrupt: %d !\n", irq_num);
		halt();
	}
}
