/* $chaos: kernel.c,v 1.2 2002/11/21 21:46:26 per Exp $ */
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
static return_t kernel_log (service_id_t service_id UNUSED, const char *string)
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
    service_register_t service_register_info;
    service_register_info.vendor = "chaos development";
    service_register_info.model = "Kernel";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &kernel_info;

    service_method_t service_method[] = 
        {
            { KERNEL_FUNCTION_LOG, (service_function_t) &kernel_log },
            { -1, NULL }
        };

    return kernel_register (&service_register_info, service_method);
}
