/* $chaos: service.c,v 1.3 2002/06/24 08:13:02 hal Exp $ */
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
return_t service_register (char *name, char *vendor, char *model, char *id,
                           unsigned int version,
                           function_t handler)
{
    service_t *service;

    return_t return_value = memory_global_allocate ((void **) &service, sizeof (service_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Make sure these fit. */
    if (string_length (name) + 1 > SERVICE_MAX_NAME_LENGTH ||
        string_length (vendor) + 1 > SERVICE_MAX_VENDOR_LENGTH ||
        string_length (model) + 1 > SERVICE_MAX_MODEL_LENGTH ||
        string_length (id) + 1 > SERVICE_MAX_ID_LENGTH)
    {
        return STORM_RETURN_INVALID_ARGUMENT; 
    }

    string_copy (service->name, name);
    string_copy (service->vendor, vendor);
    string_copy (service->model, model);
    string_copy (service->id, id);
    service->version = version;
    service->handler = handler;

    // FIXME: Use a lock here.
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
return_t service_resolve (char *name, char *vendor, char *model, char *id,
                          unsigned int version, 
                          function_t *handler)
{
    service_t *service = first_service;

    while (service != NULL)
    {
        if ((string_compare (service->name, name) == 0 && 
            service->version == version) &&
            (vendor == NULL || string_compare (service->vendor, vendor) == 0) &&
            (model == NULL || string_compare (service->model, model) == 0) &&
            (id == NULL || string_compare (service->id, id) == 0))
        {
            *handler = service->handler;
            return STORM_RETURN_SUCCESS;
        }

        service = (service_t *) service->next;
    }

    return STORM_RETURN_NOT_FOUND;
}
