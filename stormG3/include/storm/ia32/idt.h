/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Function prototypes for IDT functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_IDT_H__
#define __STORM_IA32_IDT_H__

extern void idt_setup_trap_gate (unsigned int number,
                                 unsigned int selector, void *address, 
                                 unsigned int privilege_level);

#endif /* !__STORM_IA32_IDT_H__ */
