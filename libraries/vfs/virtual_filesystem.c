/* $chaos: virtual_filesystem.c,v 1.2 2002/07/21 12:57:57 per Exp $ */
/* Abstract: Virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <virtual_filesystem/virtual_filesystem.h>

/* Resolve the first virtual filesystem service provider. FIXME:
   Should be able to return a list. */
return_t virtual_filesystem_resolve (virtual_filesystem_service_t *virtual_filesystem)
{
    size_t services;
    service_t *service;

    /* Find the virtual filesystem service. */
    if (service_resolve ("virtual_filesystem", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve virtual filesystem service provider.\n");
        return VIRTUAL_FILESYSTEM_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (virtual_filesystem);

    // FIXME: Free the memory allocated by service_resolve.

    return VIRTUAL_FILESYSTEM_RETURN_SUCCESS;
}
