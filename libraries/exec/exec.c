/* $chaos: exec.c,v 1.3 2002/10/28 07:59:43 per Exp $ */
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

    /* Find the exec service. */
    if (service_lookup ("exec", NULL, NULL, NULL, EXEC_SERVICE_MAJOR_VERSION, EXEC_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
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
    service_register_info->service_name = "exec";
    service_register_info->major_version = EXEC_SERVICE_MAJOR_VERSION;
    service_register_info->minor_version = EXEC_SERVICE_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
