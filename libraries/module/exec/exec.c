/* $chaos: exec.c,v 1.8 2002/12/08 20:00:11 per Exp $ */
/* Abstract: Exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <exec/exec.h>

/* Lookup the first exec service provider. */
// FIXME: Should be able to return a list.
return_t exec_lookup (exec_service_t *exec)
{
    // FIXME: lame
    size_t services = 1;
    service_t service;

    // FIXME: Take this as a function parameter (bug #60).
    service_lookup_t lookup =
        {
            "exec",     /* protocol_name */
            NULL,       /* service_vendor */
            NULL,       /* device_vendor */
            NULL,       /* model */
            NULL,       /* device_id */
            EXEC_PROTOCOL_MAJOR_VERSION,        /* major_version */
            EXEC_PROTOCOL_MINOR_VERSION,        /* minor_version */
        };
    
    /* Find the exec service. */
    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup exec service provider.\n");
        return EXEC_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (exec);

    return EXEC_RETURN_SUCCESS;
}

/* Register an exec service provider. */
return_t exec_register (service_register_t *service_register_info,
                        service_method_t *service_method)
{    
    service_register_info->protocol_name = "exec";
    service_register_info->major_version = EXEC_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = EXEC_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
