/* $chaos: dispatch.h,v 1.4 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                dispatch.h
 * @brief               Dispatcher prototypes.
 */

#ifndef __STORM_IA32_DISPATCH_H__
#define __STORM_IA32_DISPATCH_H__

/**
 * @brief               Initialize the dispatcher. 
 */
void dispatch_init (void);

/**
 * @brief               The task switcher -- IRQ0 handler. 
 */
void dispatch_task_switcher (void);

/**
 * @brief               The number of ticks. 
 */
extern volatile unsigned int ticks;

#endif /* !__STORM_IA32_DISPATCH_H__ */
