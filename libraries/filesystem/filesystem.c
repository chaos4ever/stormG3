/* $chaos: filesystem.c,v 1.2 2002/07/21 12:57:23 per Exp $ */
/* Abstract: Filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <filesystem/filesystem.h>

/* Lookup the first filesystem service provider. FIXME: Should be
   able to return a list. */
return_t filesystem_lookup (filesystem_service_t *filesystem)
{
    size_t services;
    service_t *service;

    /* Find the filesystem service. */
    if (service_lookup ("filesystem", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup filesystem service provider.\n");
        return FILESYSTEM_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (filesystem);

    // FIXME: Free the memory allocated by service_lookup.

    return FILESYSTEM_RETURN_SUCCESS;
}
