/* $chaos: idt.h,v 1.5 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                idt.h
 * @brief               Function prototypes for IDT functions. 
 */

#ifndef __STORM_IA32_IDT_H__
#define __STORM_IA32_IDT_H__

#include <storm/ia32/descriptor.h>

/**
 * @brief               The number of entries in the IDT. 
 */
#define IDT_ENTRIES                     (256)

/**
 * @brief               The size of the IDT.
 */
#define IDT_SIZE                        (IDT_ENTRIES * sizeof (descriptor_t))

/**
 * @brief               Create a trap gate in the IDT. 
 * @param number        The number of the IDT entry.
 * @param selector      The selector to point at.
 * @param address       The address of the function to call as the
 *                      exception handler.
 * @param privilege_level
 *                      The RPL (Requestors Privilege Level) of this gate.
 */
extern void idt_setup_trap_gate (unsigned int number,
                                 unsigned int selector, void *address, 
                                 unsigned int privilege_level);

/**
 * @brief Create an interrupt gate in the IDT. 
 * @param number        The number of the IDT entry.
 * @param selector      The selector to point at.
 * @param address       The address of the function to call as the
 *                      exception handler.
 * @param privilege_level
 *                      The RPL (Requestors Privilege Level) of this gate.
 */
extern void idt_setup_interrupt_gate (unsigned int number,
                                      unsigned int selector, 
                                      void *address, 
                                      unsigned int privilege_level);

/**
 * @brief The IDT. 
 */
extern descriptor_t idt[];

#endif /* !__STORM_IA32_IDT_H__ */
