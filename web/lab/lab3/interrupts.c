/*! Testing interrupts by priority */

#include <stdio.h>
#include <time.h>
#include <api/prog_info.h>
#include <arch/interrupt.h>

static timespec_t t = {.tv_sec = 1, .tv_nsec = 0};

void prekid(unsigned int irq_num, void *device)
{
	printf("Pocetak obrade prekida prioriteta %d\n", irq_num);
	int i;
	for (i = 0; i < 10; i++) {
		printf("Obrada prioriteta %d %d/10\n", irq_num, i+1);
		clock_nanosleep(CLOCK_REALTIME, 0, &t, NULL);
	}
	printf("Kraj obrade prekida prioriteta %d\n", irq_num);
}

int interrupts()
{
	printf("Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 interrupts_PROG_HELP);

	int i;
	for (i = 1; i < 10; i++)
		arch_register_interrupt_handler(SOFT_IRQ + i, prekid, NULL);

	while (1) {
		printf("Glavni program...\n");
		clock_nanosleep(CLOCK_REALTIME, 0, &t, NULL);
	}
	return 0;
}
