/* $chaos: keyboard.c,v 1.1 2002/06/16 21:08:00 per Exp $ */
/* Abstract: Keyboard module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

extern void module_start (void);

/* FIXME: Include a kernel header file to get these. */
typedef void (irq_handler_t)(unsigned int irq_level);

extern void debug_print (const char *format_string, ...);
extern void module_register (void);
extern unsigned int irq_register (unsigned int irq_number, char *description,
                                  irq_handler_t *function);

static void irq1_handler (unsigned int irq_number)
{
    debug_print ("%u\n", irq_number);
    asm ("inb $0x60, %al");
}

void module_start (void)
{
    module_register ();
    debug_print ("%u\n", irq_register (1, "Keyboard interrupt", &irq1_handler));
}
