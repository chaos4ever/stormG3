/* $chaos: module.h,v 1.1 2002/06/17 18:55:15 per Exp $ */
/* Abstract: Functions and variables defined by a module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_MODULE_H__
#define __STORM_MODULE_H__

#include <storm/types.h>

#ifndef STORM /* Only when included by a module. */

extern return_t module_start (void);
extern char module_name[];

#endif /* !STORM */

#endif /* !__STORM_MODULE_H__ */
