/* $chaos: kernel.c,v 1.5 2002/12/03 14:47:39 johannes Exp $ */
/* Abstract: */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             kernel.c
 * @brief            Kernel service library.
 */

#include <kernel/kernel.h>

/* Lookup the first kernel service provider. FIXME: Should be able to
   return a list. */
return_t kernel_lookup (kernel_service_t *kernel)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup;

    /* Find the exec service. */

    lookup.protocol_name = "kernel";
    lookup.major_version = KERNEL_PROTOCOL_MAJOR_VERSION;
    lookup.minor_version = KERNEL_PROTOCOL_MINOR_VERSION;

    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup kernel service provider.\n");
        return KERNEL_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (kernel);

    // FIXME: Free the memory allocated by service_lookup.
    return KERNEL_RETURN_SUCCESS;
}

/* Register a kernel service provider. */
return_t kernel_register (service_register_t *service_register_info,
                          service_method_t *service_method)
{    
    service_register_info->protocol_name = "kernel";
    service_register_info->major_version = KERNEL_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = KERNEL_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
