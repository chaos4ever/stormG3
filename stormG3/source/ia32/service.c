/* $chaos: service.c,v 1.15 2002/10/29 22:36:39 per Exp $ */
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

/* The next free service ID. We take for granted that this will not
   wrap around. If you create ten new services every second, this
   variable will wrap around after 58494241735 years. I doubt you will
   have that kind of an uptime on a chaos machine. Please prove me
   wrong! ;-) */
static uint64_t free_service_id = 0;

/* Create a new service ID. Service IDs are not reused, and that is a
   design decision that we have made, so please don't file it as a
   bug. It will not be changed. */
static service_id_t service_create_id (void)
{
    service_id_t id = free_service_id;
    free_service_id++;

    return id;
}

/* Register a service provider. */
return_t service_register (char *name, char *vendor, char *model, 
                           char *device_id,
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
        string_length (device_id) + 1 > SERVICE_ID_LENGTH)
    {
        debug_print ("%s: One of the fields were too long.\n", __FUNCTION__);
        return STORM_RETURN_INVALID_ARGUMENT; 
    }

    string_copy (service->name, name);
    string_copy (service->vendor, vendor);
    string_copy (service->model, model);
    string_copy (service->device_id, device_id);
    service->major_version = major_version;
    service->minor_version = minor_version;
    service->service_info = service_info;

    /* Locked code (non-reentrant). */
    spin_lock (&service_lock);
    service->id = service_create_id ();
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
                         const char *model, const char *device_id,
                         unsigned int major_version, 
                         unsigned int minor_version, size_t *services,
                         service_t *out_service)
{
    service_data_t *service;
    unsigned int counter = 0;
    size_t services_found = 0;

    spin_lock (&service_lock);

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
            (device_id == NULL || string_compare (service->device_id, device_id) == 0))
        {
            services_found++;
        }

        service = (service_data_t *) service->next;
    }

    /* Any matches? */
    if (services_found == 0)
    {
        spin_unlock (&service_lock);
        return STORM_RETURN_NOT_FOUND;
    }

    /* Enough space for these services? */
    if (services_found > *services)
    {
        spin_unlock (&service_lock);
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    *services = services_found;

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
            (device_id == NULL || string_compare (service->device_id, device_id) == 0))
        {
            string_copy (out_service[counter].name, service->name);
            string_copy (out_service[counter].vendor, service->vendor);
            string_copy (out_service[counter].model, service->model);
            string_copy (out_service[counter].device_id, service->device_id);
            out_service[counter].id = service->id;
            out_service[counter].major_version = service->major_version;
            out_service[counter].minor_version = service->minor_version;
            out_service[counter].service_info = service->service_info;
            counter++;
        }

        service = (service_data_t *) service->next;
    }

    spin_unlock (&service_lock);
    return STORM_RETURN_SUCCESS;
}

/* Connect to a service provider. */
return_t service_connect (service_id_t service_id UNUSED,
                          service_connection_id_t *connection_id UNUSED)
{
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Close a connection. */
return_t service_close (service_connection_id_t connection_id UNUSED)
{
    return STORM_RETURN_NOT_IMPLEMENTED;
}
