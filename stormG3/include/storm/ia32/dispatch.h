/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Dispatcher. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DISPATCH_H__
#define __STORM_IA32_DISPATCH_H__

/* The task switcher -- IRQ0 handler. */
extern void dispatch_task_switcher (void);

#endif /* !__STORM_IA32_DISPATCH_H__ */
