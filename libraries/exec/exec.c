/* $chaos: exec.c,v 1.2 2002/10/04 21:23:44 per Exp $ */
/* Abstract: Exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <exec/exec.h>

/* Lookup the first exec service provider. FIXME: Should be able to
   return a list. */
return_t exec_lookup (exec_service_t *exec)
{
    size_t services;
    service_t *service;

    /* Find the exec service. */
    if (service_lookup ("exec", NULL, NULL, NULL, EXEC_SERVICE_MAJOR_VERSION, EXEC_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup exec service provider.\n");
        return EXEC_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (exec);

    // FIXME: Free the memory allocated by service_lookup.
    return EXEC_RETURN_SUCCESS;
}

/* Register an exec service provider. */
return_t exec_register (char *vendor, char *model, char *id,
                        service_info_t service_info)
{    
    return service_register ("exec", vendor, model, id, EXEC_SERVICE_MAJOR_VERSION, EXEC_SERVICE_MINOR_VERSION, service_info);
}
