/* $chaos: dotfile.emacs,v 1.37 2002/10/14 16:03:33 per Exp $ */
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
    size_t services;
    service_t *service;

    /* Find the exec service. */
    if (service_lookup ("kernel", NULL, NULL, NULL, KERNEL_SERVICE_MAJOR_VERSION, KERNEL_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup kernel service provider.\n");
        return KERNEL_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (kernel);

    // FIXME: Free the memory allocated by service_lookup.
    return KERNEL_RETURN_SUCCESS;
}

/* Register an kernel service provider. */
return_t kernel_register (char *vendor, char *model, char *id,
                          service_info_t service_info)
{    
    return service_register ("kernel", vendor, model, id, KERNEL_SERVICE_MAJOR_VERSION, KERNEL_SERVICE_MINOR_VERSION, service_info);
}
