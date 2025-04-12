/*! Program info */
#pragma once

#include <types/basic.h>

/* "programs" */
int hello_world();
int timer();
int keyboard();
int interrupts();

#define	hello_world_PROG_HELP	"Print 'Hello world'."
#define	timer_PROG_HELP		"Timer interface demonstration: "	\
				"periodic timer activations."
#define	keyboard_PROG_HELP	"Print ASCII code for each keystroke. "	\
				"Press '.' to end."
#define	interrupts_PROG_HELP	"Simulated interrupts."
