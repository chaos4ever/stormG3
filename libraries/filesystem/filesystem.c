/* $chaos: filesystem.c,v 1.5 2002/10/28 08:06:42 per Exp $ */
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

    /* Find the filesystem service. */
    if (service_lookup ("filesystem", NULL, NULL, NULL, FILESYSTEM_SERVICE_MAJOR_VERSION, FILESYSTEM_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup filesystem service provider.\n");
        return FILESYSTEM_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (filesystem);

    return FILESYSTEM_RETURN_SUCCESS;
}
