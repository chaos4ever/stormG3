/* $chaos: dotfile.emacs,v 1.37 2002/10/14 16:03:33 per Exp $ */
/* Abstract: System call prototypes etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                system_call.h
 * @brief               System call implementation.
 */

#ifndef __STORM_IA32_SYSTEM_CALL_H__
#define __STORM_IA32_SYSTEM_CALL_H__

/**
 * @brief               The system call vector in the IDT. 
 */
#define SYSTEM_CALL_IDT_ENTRY \
                        (0x88)

/* Only in the kernel. */
#ifdef __STORM_KERNEL__

/**
 * @brief               Set up the system call in the IDT.
 */
extern void system_call_init (void);

/**
 * @brief               The low-level system call handler.
 */
extern void system_call_lowlevel (void);

/**
 * @brief               The high-level system call handler.
 */
extern void system_call (void);

#endif /* __STORM_KERNEL__ */

#endif /* !__STORM_IA32_SYSTEM_CALL_H__ */
