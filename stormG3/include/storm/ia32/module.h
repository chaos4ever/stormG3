/* $chaos: module.h,v 1.2 2002/06/16 21:48:42 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_MODULE_H__
#define __STORM_IA32_MODULE_H__

/* Type definitions. */
/* A function provided to the kernel modules. */
typedef struct
{
    char *name;
    function_t function;
} module_function_t;

/* Initialize module support. */
extern void module_init (void);

/* Register a module with the kernel. */
extern void module_register (void);

#endif /* !__STORM_IA32_MODULE_H__ */
