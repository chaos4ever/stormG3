/* $chaos: vfs.c,v 1.6 2002/10/28 08:09:29 per Exp $ */
/* Abstract: Virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <vfs/vfs.h>

/* Lookup the first virtual filesystem service provider. FIXME:
   Should be able to return a list. */
return_t vfs_lookup (vfs_service_t *vfs)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;

    /* Find the virtual filesystem service. */
    if (service_lookup ("vfs", NULL, NULL, NULL, VFS_SERVICE_MAJOR_VERSION, VFS_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup virtual filesystem service provider.\n");
        return VFS_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (vfs);

    return VFS_RETURN_SUCCESS;
}

/* Register a VFS service provider. */
return_t vfs_register (service_register_t *service_register_info,
                       service_method_t *service_method)
{    
    service_register_info->service_name = "vfs";
    service_register_info->major_version = VFS_SERVICE_MAJOR_VERSION;
    service_register_info->minor_version = VFS_SERVICE_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
