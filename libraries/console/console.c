/* $chaos: console.c,v 1.2 2002/07/04 21:25:52 per Exp $ */
/* Abstract: Console library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <stdarg.h>
#include <console/console.h>
#include <string/string.h>

/* Initialise a connection between the application and the console
   service. */
return_t console_init (console_service_t *console)
{
    size_t services;
    service_t *service;

    /* Find the console service. */
    if (service_resolve ("console", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve console service provider.\n");
        return CONSOLE_RETURN_SERVICE_UNAVAILABLE;
    }
    service[0].service_info (console);

    // FIXME: Free the memory allocated by service_resolve.

    return CONSOLE_RETURN_SUCCESS;
}

