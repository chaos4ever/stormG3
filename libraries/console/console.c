/* $chaos: console.c,v 1.8 2002/11/20 20:03:29 per Exp $ */
/* Abstract: Console library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <stdarg.h>
#include <console/console.h>

/* Initialize a connection between the application and the console
   service. */
return_t console_lookup (console_service_t *console)
{
    // FIXME: Fix this fulkod ASAP.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup;

    /* Find the console service. */

    lookup.protocol_name = "console";
    lookup.major_version = CONSOLE_PROTOCOL_MAJOR_VERSION;
    lookup.minor_version = CONSOLE_PROTOCOL_MINOR_VERSION;
    
    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup console service provider.\n");
        return CONSOLE_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (console);

    // FIXME: Free the memory allocated by service_resolve.

    return CONSOLE_RETURN_SUCCESS;
}

/* Register a console service provider. */
return_t console_register (service_register_t *service_register_info,
                           service_method_t *service_method)
{    
    service_register_info->protocol_name = "console";
    service_register_info->major_version = CONSOLE_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = CONSOLE_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
