/* $chaos: dotfile.emacs,v 1.37 2002/10/14 16:03:33 per Exp $ */
/* Abstract: Kernel module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             kernel.c
 * @brief            Kernel module.
 */

#include <kernel/kernel.h>

/* Print a log message. */
static return_t kernel_log (const char *string)
{
    debug_print (string);
    return STORM_RETURN_SUCCESS;
}

/* Return some information about the kernel service. */
static return_t kernel_info (void *kernel_void)
{
    kernel_service_t *kernel = (kernel_service_t *) kernel_void;

    kernel->log = kernel_log;
    return STORM_RETURN_SUCCESS;
}

/* The module entry point. */
return_t module_start (void)
{
    return kernel_register ("chaos development", "Kernel", "1", &kernel_info);
}
