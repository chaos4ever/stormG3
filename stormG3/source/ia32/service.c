/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/service.h>
#include <storm/ia32/string.h>

/* Services are stored in a linked list for now. */
static service_t *first_service = NULL;

/* Register a service provider. */
return_t service_register (char *name, unsigned int version,
                           function_t handler)
{
    service_t *service;

    return_t return_value = memory_global_allocate ((void **) &service, sizeof (service_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    // FIXME: Need to copy this to a buffer of our own, really.
    service->name = name;

    service->version = version;
    service->handler = handler;
    service->next = (struct service_t *) first_service;
    first_service = service;
    return STORM_RETURN_SUCCESS;
}

/* Unregister a service provider. */
return_t service_unregister (char *service __attribute__ ((unused)),
                             function_t handler __attribute__ ((unused)))
{
    // FIXME: Write this.
    return STORM_RETURN_SUCCESS;
}

/* Resolve a service. FIXME: Support multiple service providers. */
return_t service_resolve (char *name, unsigned int version, 
                          function_t *handler)
{
    service_t *service = first_service;
    while (service != NULL)
    {
        if (string_compare (service->name, name) == 0 && 
            service->version == version)
        {
            *handler = service->handler;
            return STORM_RETURN_SUCCESS;
        }
    }

    return STORM_RETURN_NOT_FOUND;
}
