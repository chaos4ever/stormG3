/* $chaos: exec.c,v 1.6 2002/12/03 14:21:31 johannes Exp $ */
/* Abstract: Exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <exec/exec.h>

/* Lookup the first exec service provider. FIXME: Should be able to
   return a list. */
return_t exec_lookup (exec_service_t *exec)
{
    // FIXME: lame
    size_t services = 1;
    service_t service;
    service_lookup_t lookup;

    /* Find the exec service. */

    lookup.protocol_name = "exec";
    lookup.device_vendor = NULL;
    lookup.service_vendor = NULL;
    lookup.major_version = EXEC_PROTOCOL_MAJOR_VERSION;
    lookup.minor_version = EXEC_PROTOCOL_MINOR_VERSION;

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
