/* $chaos: log.c,v 1.6 2002/10/04 19:00:55 per Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <log/log.h>

/* Get a connection to the log service provider. */
return_t log_lookup (log_service_t *log)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_lookup ("log", NULL, NULL, NULL, LOG_SERVICE_MAJOR_VERSION, LOG_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (log);

    // FIXME: Free the memory allocated by service_lookup.

    return LOG_RETURN_SUCCESS;
}
