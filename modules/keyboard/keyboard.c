/* $chaos: keyboard.c,v 1.2 2002/06/17 07:27:27 per Exp $ */
/* Abstract: Keyboard module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>

/* The module name. Fetched by the kernel and put into a data
   structure. */
char module_name[] = "keyboard";

static void irq1_handler (unsigned int irq_number)
{
    debug_print ("%u ", irq_number);
    asm ("inb $0x60, %al");
}

void module_start (void)
{
    debug_print ("%u\n", irq_register (1, "Keyboard interrupt", &irq1_handler));
}
