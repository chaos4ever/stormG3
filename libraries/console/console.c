/* $chaos: console.c,v 1.3 2002/05/23 11:14:26 per Exp $ */
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
        debug_print ("Failed to resolved log service provider.\n");
        return CONSOLE_RETURN_SERVICE_UNAVAILABLE;
    }
    service[0].service_info (console);

    return CONSOLE_RETURN_SUCCESS;
}

