/* $chaos: idt.h,v 1.2 2002/06/14 12:34:27 per Exp $ */
/* Abstract: Function prototypes for IDT functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_IDT_H__
#define __STORM_IA32_IDT_H__

#include <storm/ia32/descriptor.h>

/* Defines. */
/* The number of entries in the IDT. */
#define IDT_ENTRIES                     (256)

#define IDT_SIZE                        (IDT_ENTRIES * sizeof (descriptor_t))

/* Function prototypes. */
/* Create a trap gate in the IDT. */
extern void idt_setup_trap_gate (unsigned int number,
                                 unsigned int selector, void *address, 
                                 unsigned int privilege_level);

/* Create an interrupt gate in the IDT. */
extern void idt_setup_interrupt_gate (unsigned int number,
                                      unsigned int selector, 
                                      void *address, 
                                      unsigned int privilege_level);

/* External variables. */
/* The IDT. */
extern descriptor_t idt[];

#endif /* !__STORM_IA32_IDT_H__ */
