/* $chaos: module.h,v 1.3 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file ia32/module.h
 * @brief IA32-specific parts of the module support. 
 */

#ifndef __STORM_IA32_MODULE_H__
#define __STORM_IA32_MODULE_H__

/* Type definitions. */
/** @brief A function provided to the kernel modules. */
typedef struct
{
    char *name;
    function_t function;
} module_function_t;

/** @brief Initialize module support. */
extern void module_init (void);

/** @brief Register a module with the kernel. */
extern void module_register (void);

#endif /* !__STORM_IA32_MODULE_H__ */
