/* $chaos: vfs.c,v 1.1 2002/07/28 19:30:54 per Exp $ */
/* Abstract: Virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <vfs/vfs.h>

/* Resolve the first virtual filesystem service provider. FIXME:
   Should be able to return a list. */
return_t vfs_resolve (vfs_service_t *vfs)
{
    size_t services;
    service_t *service;

    /* Find the virtual filesystem service. */
    if (service_resolve ("virtual_filesystem", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve virtual filesystem service provider.\n");
        return VFS_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (vfs);

    // FIXME: Free the memory allocated by service_resolve.
    return VFS_RETURN_SUCCESS;
}

// TODO: Add a vfs_register function for registering a vfs service
// provider.
