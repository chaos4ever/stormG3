/* $chaos: types.h,v 1.9 2002/10/04 19:01:19 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file storm/types.h
    @brief storm types. */

#ifndef __STORM_TYPES_H__
#define __STORM_TYPES_H__

#include <stdint.h>

/* Type definitions. */
/** @brief A size. */
typedef int size_t;

/** @brief A return value (STORM_RETURN_*) */
typedef int return_t;

/** @brief A function pointer. */
typedef return_t (*function_t)(void);   /* Can be used even if the
                                           function uses arguments. */
typedef int bool;                       /* no _t, since this should
                                           really have been a built-in
                                           type in C. */

#endif /* !__STORM_TYPES_H__ */
