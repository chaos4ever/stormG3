/* $chaos: service.c,v 1.12 2002/10/28 07:52:18 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/service.h>
#include <storm/ia32/string.h>

/* Services are stored in a linked list for now. */
static service_data_t *first_service = NULL;

/* Lock used to protect the service data structure. */
static spinlock_t service_lock = SPIN_UNLOCKED;

/* Register a service provider. */
return_t service_register (char *name, char *vendor, char *model, char *id,
                           unsigned int major_version,
                           unsigned int minor_version,
                           service_info_t service_info)
{
    service_data_t *service;

    return_t return_value = memory_global_allocate ((void **) &service, sizeof (service_data_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("%s: Allocating memory failed.\n", __FUNCTION__);
        return return_value;
    }

    /* Make sure these fit. */
    if (string_length (name) + 1 > SERVICE_NAME_LENGTH ||
        string_length (vendor) + 1 > SERVICE_VENDOR_LENGTH ||
        string_length (model) + 1 > SERVICE_MODEL_LENGTH ||
        string_length (id) + 1 > SERVICE_ID_LENGTH)
    {
        debug_print ("%s: One of the fields were too long.\n", __FUNCTION__);
        return STORM_RETURN_INVALID_ARGUMENT; 
    }

    string_copy (service->name, name);
    string_copy (service->vendor, vendor);
    string_copy (service->model, model);
    string_copy (service->id, id);
    service->major_version = major_version;
    service->minor_version = minor_version;
    service->service_info = service_info;

    spin_lock (&service_lock);
    service->next = (struct service_data_t *) first_service;
    first_service = service;
    spin_unlock (&service_lock);
    return STORM_RETURN_SUCCESS;
}

/* Unregister a service provider. */
return_t service_unregister (char *service UNUSED,
                             function_t handler UNUSED)
{
    // FIXME: Write this.
    return STORM_RETURN_SUCCESS;
}

/* Lookup a service. */
return_t service_lookup (const char *name, const char *vendor, 
                         const char *model, const char *id,
                         unsigned int major_version, 
                         unsigned int minor_version, size_t *services,
                         service_t **out_service)
{
    service_data_t *service;
    unsigned int counter = 0;

    spin_lock (&service_lock);

    (*services) = 0;
    
    /* Iterate two times. The first time is used to calculate the
       number of matching services. */
    service = first_service;
    while (service != NULL)
    {
        /* We take the fast (integer) comparisons first so that we be
           efficient. */
        if ((service->major_version == major_version) &&
            (service->minor_version >= minor_version) &&
            string_compare (service->name, name) == 0 && 
            (vendor == NULL || string_compare (service->vendor, vendor) == 0) &&
            (model == NULL || string_compare (service->model, model) == 0) &&
            (id == NULL || string_compare (service->id, id) == 0))
        {
            (*services)++;
        }

        service = (service_data_t *) service->next;
    }

    /* Any matches? */
    if ((*services) == 0)
    {
        spin_unlock (&service_lock);
        return STORM_RETURN_NOT_FOUND;
    }

    /* Allocate memory for the data structure. We can only allocate
       max 4 KiB this way, but since one service is less than 128
       byte, that's at least 32 service providers anyway. Bill Gates,
       I love you! :-) We should use memory_virtual_allocate
       anyway.. (at least for proceses) */
    if (memory_global_allocate ((void **) out_service, (*services) * sizeof (service_t)) != STORM_RETURN_SUCCESS)
    {
        spin_unlock (&service_lock);
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    /* Start doing our business. */
    service = first_service;
    while (service != NULL)
    {
        /* Numeric comparisons are fast so we do them first. */
        if (service->major_version == major_version &&
            service->minor_version >= minor_version &&
            string_compare (service->name, name) == 0 && 
            (vendor == NULL || string_compare (service->vendor, vendor) == 0) &&
            (model == NULL || string_compare (service->model, model) == 0) &&
            (id == NULL || string_compare (service->id, id) == 0))
        {
            string_copy ((*out_service)[counter].name, service->name);
            string_copy ((*out_service)[counter].vendor, service->vendor);
            string_copy ((*out_service)[counter].model, service->model);
            string_copy ((*out_service)[counter].id, service->id);
            (*out_service)[counter].major_version = service->major_version;
            (*out_service)[counter].minor_version = service->minor_version;
            (*out_service)[counter].service_info = service->service_info;
            counter++;
        }

        service = (service_data_t *) service->next;
    }

    spin_unlock (&service_lock);
    return STORM_RETURN_SUCCESS;
}
