/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: vfs_mount () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "vfs.h"

/* Mount the given block device into the given path. */
return_t vfs_mount (char *path, block_service_t *block)
{
    mount_t *new_mount;
    return_t return_value;
    filesystem_service_t filesystem;

    if (!is_virtual (path))
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Probe the available file system service providers to see if
       this volume is a valid file system. */
    return_value = filesystem_resolve (&filesystem);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    // FIXME: Resolve multiple file systems. For now, just take the
    // one that we get and try it.
    filesystem.mount (block);

    return_value = memory_global_allocate ((void **) &new_mount, sizeof (mount_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    // FIXME: Locking from here...
    new_mount->next = (struct mount_t *) first_mount;
    string_copy_max (new_mount->path, path, VIRTUAL_PATH_MAX);
    memory_copy (&new_mount->block, block, sizeof (block_service_t));
    memory_copy (&new_mount->filesystem, &filesystem, sizeof (filesystem_service_t));
    first_mount = new_mount;
    // FIXME: ...to here.

    return STORM_RETURN_SUCCESS;
}
