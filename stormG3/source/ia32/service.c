/* $chaos: service.c,v 1.22 2002/12/01 22:57:42 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/service.h>
#include <storm/ia32/string.h>

/* Services are stored in this doubly-linked list. */
static service_data_t *service_list = NULL;

/* Lock used to protect the service and method lists. */
static spinlock_t service_lock = SPIN_UNLOCKED;

/* Connections are stored in this list. */
static service_connection_t *connection_list = NULL;

/* Lock used to protect the connection list. */
static spinlock_t connection_lock = SPIN_UNLOCKED;

/* The next free service ID. We take for granted that this will not
   wrap around. If you create ten new services every second, this
   variable will wrap around after 58494241735 years. I doubt you will
   have that kind of an uptime on a chaos machine. Please prove me
   wrong! ;-) */
static service_id_t free_service_id = 0;

/* The next free connection ID. */
static service_connection_id_t free_connection_id = 0;

/* List of methods in our service providers (could be a hash table for
   faster access). Locked via service_lock. */
static service_method_data_t *method_list = NULL;

/* Create a new service ID. Service IDs are not reused, and that is a
   design decision that we have made, so please don't file it as a
   bug. It will not be changed. */
static service_id_t service_create_id (void)
{
    service_id_t id = free_service_id;
    free_service_id++;

    return id;
}

/* Create a new connection ID. */
static service_id_t service_create_connection_id (void)
{
    service_connection_id_t id = free_connection_id;
    free_connection_id++;

    return id;
}

/* Find a service provider by ID. The caller needs to lock the
   service_lock! */
static service_data_t *service_find_by_id (service_id_t service_id)
{
    if (service_lock == SPIN_UNLOCKED)
    {
        DEBUG_HALT ("Kernel bug: you need to lock the service_lock before calling this function");
    }

    service_data_t *list = service_list;

    while (list != NULL)
    {
        if (list->id == service_id)
        {
            break;
        }

        list = (service_data_t *) list->next;
    }

    return list;
}

/* Find a connection by ID. */
static service_connection_t *service_connection_find_by_id (service_connection_id_t connection_id)
{
    if (connection_lock == SPIN_UNLOCKED)
    {
        DEBUG_HALT ("Kernel bug: you need to lock the connection_lock before calling this function");
    }

    service_connection_t *list = connection_list;

    while (list != NULL)
    {
        if (list->id == connection_id)
        {
            break;
        }

        list = (service_connection_t *) list->next;
    }

    return list;
}

/* Register a method in a service provider. This function takes for
   granted that service_lock has been acquired. */
static return_t service_register_method (service_id_t service_id, service_method_id_t method_id, service_function_t method_handler)
{
    if (service_lock == SPIN_UNLOCKED)
    {
        DEBUG_HALT ("Kernel bug: you need to lock the service_lock before calling this function");
    }

    /* Allocate a new node. */
    service_method_data_t *method;
    return_t return_value = memory_global_allocate ((void **) &method, sizeof (service_method_data_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_INFO();
        return return_value;
    }

    if (method_list != NULL)
    {
        method_list->previous = (struct service_method_data_t *) method;
    }

    method->previous = NULL;
    method->next = (struct service_method_data_t *) method_list;
    method->service_id = service_id;
    method->method_id = method_id;
    method->method = method_handler;
    method_list = method;

    return STORM_RETURN_SUCCESS;
}

/* Find the given method in the given service provider. This function
   takes for granted that service_lock has been acquired. */
static service_function_t service_find_method (service_id_t service_id, service_method_id_t method_id)
{
    if (service_lock == SPIN_UNLOCKED)
    {
        DEBUG_HALT ("Kernel bug: you need to lock the service_lock before calling this function");
    }

    service_method_data_t *method = method_list;

    while (method != NULL)
    {
        if (method->service_id == service_id && 
            method->method_id == method_id)
        {
            break;
        }

        method = (service_method_data_t *) method->next;
    }

    return method->method;
}

/* Register a service provider. */
return_t service_register (service_register_t *register_info,
                           service_method_t *method)
{
    service_data_t *service;

    /* Check the input parameters. */
    if (register_info == NULL ||
        method == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Allocate memory for the node. */
    return_t return_value = memory_global_allocate ((void **) &service, sizeof (service_data_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("%s: Allocating memory failed.\n", __FUNCTION__);
        return return_value;
    }

    /* Make sure these fit. */
    if (string_length (register_info->protocol_name) + 1 > SERVICE_PROTOCOL_NAME_LENGTH ||
        string_length (register_info->device_vendor) + 1 > SERVICE_DEVICE_VENDOR_LENGTH ||
        string_length (register_info->service_vendor) + 1 > SERVICE_VENDOR_LENGTH ||
        string_length (register_info->model) + 1 > SERVICE_MODEL_LENGTH ||
        string_length (register_info->device_id) + 1 > SERVICE_ID_LENGTH)
    {
        debug_print ("%s: One of the fields were too long.\n", __FUNCTION__);
        return STORM_RETURN_INVALID_ARGUMENT; 
    }

    /* Copy the strings to our service node. */
    string_copy (service->protocol_name, register_info->protocol_name);
    string_copy (service->service_vendor, register_info->service_vendor);
    string_copy (service->device_vendor, register_info->device_vendor);
    string_copy (service->model, register_info->model);
    string_copy (service->device_id, register_info->device_id);
    service->major_version = register_info->major_version;
    service->minor_version = register_info->minor_version;
    service->service_info = register_info->info_handler;
    service->reference_count = 0;

    /* Locked code (non-reentrant). */
    spin_lock (&service_lock);
    service->id = service_create_id ();
    service->next = (struct service_data_t *) service_list;

    service_list = service;

    /* We need to register the service method handlers here, while the
       lock is locked. Otherwise, we could get weird bugs. */
    size_t count = 0;
    while (method[count].method != NULL)
    {
        service_register_method (service->id, method[count].method_id,
                                 method[count].method);
        count++;
    }    

    spin_unlock (&service_lock);
    return STORM_RETURN_SUCCESS;
}

/* Unregister a service provider. */
return_t service_unregister (service_id_t service_id UNUSED)
{
    // BUG #45: Implement this.
    return STORM_RETURN_SUCCESS;
}

/* Lookup a service. */
return_t service_lookup (service_lookup_t *lookup, size_t *services,
                         service_t *out_service)
{
    service_data_t *service;
    unsigned int counter = 0;
    size_t services_found = 0;

    spin_lock (&service_lock);

    /* Iterate two times. The first time is used to calculate the
       number of matching services. */
    service = service_list;
    while (service != NULL)
    {
        /* We take the fast (integer) comparisons first so that we be
           efficient. */
        if ((service->major_version == lookup->major_version) &&
            (service->minor_version >= lookup->minor_version) &&
            string_compare (service->protocol_name, lookup->protocol_name) == 0 && 
            (lookup->service_vendor == NULL ||
             string_compare (service->service_vendor,
                             lookup->service_vendor) == 0) &&
            (lookup->device_vendor == NULL ||
             string_compare (service->device_vendor,
                             lookup->device_vendor) == 0) &&
            (lookup->model == NULL || 
             string_compare (service->model, lookup->model) == 0) &&
            (lookup->device_id == NULL || 
             string_compare (service->device_id, lookup->device_id) == 0))
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
        DEBUG_INFO();
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    *services = services_found;

    /* Start doing our business. */
    service = service_list;
    while (service != NULL)
    {
        /* Numeric comparisons are fast so we do them first. */
        if (service->major_version == lookup->major_version &&
            service->minor_version >= lookup->minor_version &&
            string_compare (service->protocol_name, 
                            lookup->protocol_name) == 0 && 
            (lookup->service_vendor == NULL ||
             string_compare (service->service_vendor, 
                             lookup->service_vendor) == 0) &&
            (lookup->device_vendor == NULL ||
             string_compare (service->device_vendor, 
                             lookup->device_vendor) == 0) &&
            (lookup->model == NULL || 
             string_compare (service->model, lookup->model) == 0) &&
            (lookup->device_id == NULL ||
             string_compare (service->device_id, lookup->device_id) == 0))
        {
            string_copy (out_service[counter].protocol_name, service->protocol_name);
            string_copy (out_service[counter].device_vendor,
                         service->device_vendor);
            string_copy (out_service[counter].service_vendor,
                         service->service_vendor);
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
return_t service_connect (service_id_t service_id,
                          service_connection_id_t *connection_id)
{
    /* Find this service provider. */
    spin_lock (&service_lock);
    service_data_t *service_data = service_find_by_id (service_id);
    spin_unlock (&service_lock);

    /* Make sure this service exists. */
    if (service_data == NULL)
    {
        DEBUG_INFO();
        return STORM_RETURN_NOT_FOUND;
    }

    /* Allocate memory for the connection. */
    service_connection_t *service_connection;
    return_t return_value = memory_global_allocate ((void **) &service_connection, sizeof (service_connection_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_INFO();
        return return_value;
    }

    /* Increase the reference count (to handle unregister properly). */
    spin_lock (&service_lock);
    service_data->reference_count++;
    spin_unlock (&service_lock);

    /* Initialize the data structure. */
    service_connection->process = dispatch_current_process;
    service_connection->service = service_data;
    service_connection->previous = (struct service_connection_t *) connection_list;
    service_connection->next = NULL;

    /* Add this connection to the list of connections. */
    spin_lock (&connection_lock);
    service_connection->id = service_create_connection_id ();
    *connection_id = service_connection->id;
    if (connection_list != NULL)
    {
        connection_list->next = (struct service_connection_t *) service_connection;
    }
    connection_list = service_connection;
    spin_unlock (&connection_lock);

    return STORM_RETURN_SUCCESS;
}

/* Close a connection. */
return_t service_close (service_connection_id_t connection_id)
{
    DEBUG_INFO();
    /* Find the connection. */
    service_connection_t *connection = service_connection_find_by_id (connection_id);
    
    if (connection == NULL)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure it's owned by us. */
    if (connection->process != dispatch_current_process)
    {
        return STORM_RETURN_ACCESS_DENIED;
    }

    spin_lock (&service_lock);
    connection->service->reference_count++;
    spin_unlock (&service_lock);

    /* It's ours, we can unlink it. */
    spin_lock (&connection_lock);
    service_connection_t *previous = (service_connection_t *) connection->previous;
    service_connection_t *next = (service_connection_t *) connection->next;

    if (previous != NULL)
    {
        previous->next = (struct service_connection_t *) next;
    }
    
    if (next != NULL)
    {
        next->previous = (struct service_connection_t *) previous;
    }

    /* If this is the first item in the list, change the list to point
       to the next item. */
    if (connection_list == connection)
    {
        connection_list = next;
    }
    spin_unlock (&connection_lock);

    return STORM_RETURN_SUCCESS;
}

/* Invoke a method in a service. */
return_t service_invoke (service_connection_id_t connection_id, 
                         service_method_id_t method_id, void *data)
{
    /* Find the connection. */
    spin_lock (&connection_lock);
    service_connection_t *connection = service_connection_find_by_id (connection_id);
    spin_unlock (&connection_lock);

    if (connection == NULL)
    {
        DEBUG_INFO();
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Look this function up. */
    spin_lock (&service_lock);

    service_function_t function = service_find_method (connection->service->id, method_id);
    spin_unlock (&service_lock);

    if (function == NULL)
    {
        DEBUG_INFO();
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    return function (connection->service->id, data);
}
