/* $chaos: main.h,v 1.3 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file main.h
 * @brief System startup.
 */

#ifndef __STORM_IA32_MAIN_H__
#define __STORM_IA32_MAIN_H__

/**
 * @brief Run the system startup.
 *
 * This is the startup point of storm. It is executed right
 * after the assembly language init code has set up the GDT, kernel
 * stack, etc. Here, we initialise everything in the storm, like
 * IRQ/exception handling, the timer hardware, the memory facilities
 * of the host CPU and multitasking. It is also responsible for
 * starting the servers loaded by the Multiboot compliant boot
 * loader. 
 */
extern void main_bootup (int argument_count, char *arguments[]);

#endif /* !__STORM_IA32_MAIN_H__ */
