/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Functions and variables defined by a module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_MODULE_H__
#define __STORM_MODULE_H__

#ifndef STORM /* Only when included by a module. */

extern void module_start (void);
extern char module_name[];

#endif /* !STORM */

#endif /* !__STORM_MODULE_H__ */
