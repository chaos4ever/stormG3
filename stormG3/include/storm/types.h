/* $chaos: types.h,v 1.6 2002/06/16 16:37:11 per Exp $ */
/* Abstract: storm types. */
/* Author: Per Lundberg <per@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_TYPES_H__
#define __STORM_TYPES_H__

#include <stdint.h>

/* Type definitions. */
typedef int size_t;
typedef int return_t;
typedef void (*function_t)(void);       /* Can be used even if the
                                           function uses arguments. */
typedef int bool;                       /* no _t, since this should
                                           really have been a built-in
                                           type in C. */

#endif /* !__STORM_TYPES_H__ */
