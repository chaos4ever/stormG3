/* $chaos: filesystem.c,v 1.7 2002/11/20 20:02:53 per Exp $ */
/* Abstract: Filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <filesystem/filesystem.h>

/* Lookup the first filesystem service provider. FIXME: Should be
   able to return a list. */
return_t filesystem_lookup (filesystem_service_t *filesystem)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup;

    /* Find the filesystem service. */

    lookup.protocol_name = "filesystem";
    lookup.device_vendor = NULL;
    lookup.service_vendor = NULL;
    lookup.major_version = FILESYSTEM_PROTOCOL_MAJOR_VERSION;
    lookup.minor_version = FILESYSTEM_PROTOCOL_MINOR_VERSION;

    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup filesystem service provider.\n");
        return FILESYSTEM_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (filesystem);

    return FILESYSTEM_RETURN_SUCCESS;
}

/* Register a filesystem service provider. */
return_t filesystem_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "filesystem";
    service_register_info->major_version = FILESYSTEM_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = FILESYSTEM_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
