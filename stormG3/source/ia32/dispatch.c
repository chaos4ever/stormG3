/* $chaos: dispatch.c,v 1.3 2002/07/21 09:58:21 per Exp $ */
/* Abstract: Dispatcher. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/defines.h>
#include <storm/ia32/dispatch.h>

/* The number of ticks since IRQ0 was first enabled. */
volatile unsigned int ticks = 0;

/* The task switcher -- IRQ0 handler (called from irq_handlers.S that
   does the register preservation. */
void dispatch_task_switcher (void)
{
    asm ("incl ticks\n"
         "movl 0xB8000, %eax\n"
         "xorl $0x10001000, %eax\n"
         "movl %eax, 0xB8000\n");
}


