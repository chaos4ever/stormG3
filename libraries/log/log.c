/* $chaos: log.c,v 1.9 2002/11/20 20:04:31 per Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <log/log.h>

/* Get a connection to the log service provider. */
return_t log_lookup (log_service_t *log)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup;

    /* Find the log service. */

    lookup.protocol_name = "log";
    lookup.major_version = LOG_PROTOCOL_MAJOR_VERSION;
    lookup.minor_version = LOG_PROTOCOL_MINOR_VERSION;

    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (log);

    return LOG_RETURN_SUCCESS;
}

/* Register a log service provider. */
return_t log_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "log";
    service_register_info->major_version = LOG_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = LOG_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
