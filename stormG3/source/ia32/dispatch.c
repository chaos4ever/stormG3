/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Dispatcher. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/defines.h>
#include <storm/ia32/dispatch.h>

/* The task switcher -- IRQ0 handler. */
void dispatch_task_switcher (void)
{
    /* Return straight away for now. */
    asm ("notl 0xB8000\n"
         "movb $0x20, %al\n"
         "outb %al, $0x20");
    asm ("iret");

    /* Just to make gcc happy, so that it will know that this function
       will never return... */
    while (TRUE);
}
