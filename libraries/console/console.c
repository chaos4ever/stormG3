/* $chaos: console.c,v 1.6 2002/10/28 07:58:00 per Exp $ */
/* Abstract: Console library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <stdarg.h>
#include <console/console.h>
#include <string/string.h>

/* Initialize a connection between the application and the console
   service. */
return_t console_lookup (console_service_t *console)
{
    // FIXME: Fix this fulkod ASAP.
    size_t services = 1;
    service_t service;

    /* Find the console service. */
    if (service_lookup ("console", NULL, NULL, NULL, CONSOLE_SERVICE_MAJOR_VERSION, CONSOLE_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
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
    service_register_info->service_name = "console";
    service_register_info->major_version = CONSOLE_SERVICE_MAJOR_VERSION;
    service_register_info->minor_version = CONSOLE_SERVICE_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
