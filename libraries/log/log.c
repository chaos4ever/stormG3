/* $chaos: log.c,v 1.7 2002/10/28 08:08:15 per Exp $ */
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

    /* Find the log service. */
    if (service_lookup ("log", NULL, NULL, NULL, LOG_SERVICE_MAJOR_VERSION, LOG_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
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
    service_register_info->service_name = "log";
    service_register_info->major_version = LOG_SERVICE_MAJOR_VERSION;
    service_register_info->minor_version = LOG_SERVICE_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
