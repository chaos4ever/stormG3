/* $chaos: dispatch.h,v 1.1 2002/06/15 13:48:56 per Exp $ */
/* Abstract: Dispatcher. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DISPATCH_H__
#define __STORM_IA32_DISPATCH_H__

/* The task switcher -- IRQ0 handler. */
extern void dispatch_task_switcher (void);

/* The number of ticks. */
extern volatile unsigned int ticks;

#endif /* !__STORM_IA32_DISPATCH_H__ */
