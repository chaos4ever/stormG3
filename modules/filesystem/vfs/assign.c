/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: vfs_assign () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

/* Assign a directory in the virtual file system (with the root as //)
   into the logical file system (with the root /). */

#include "vfs.h"

/* Assign a virtual path to a logical. */
return_t vfs_assign (char *virtual, char *logical)
{
    assign_t *new_assign;
    mount_t *mount;

    if (!is_virtual (virtual))
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    if (!is_logical (logical))
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    mount = find_mount (virtual);
    if (mount == NULL)
    {
        return STORM_RETURN_NOT_FOUND;
    }
    
    // TODO: Check whether this logical mount point has been
    // previously mounted. Also, make sure its parent exists. For now,
    // we just presume that both the virtual and logical parts are in
    // their roots.

    return_t return_value = memory_global_allocate ((void **) &new_assign, sizeof (assign_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }
    
    // FIXME: Locking from here...
    new_assign->next = (struct assign_t *) first_assign;
    // FIXME!!! We need to find the mount point corresponding to this
    // assignment.
    new_assign->mount = first_mount;
    string_copy_max (new_assign->virtual_path, virtual, VIRTUAL_PATH_MAX);
    string_copy_max (new_assign->logical_path, logical, LOGICAL_PATH_MAX);
    first_assign = new_assign;
    // FIXME: ...to here.

    return STORM_RETURN_SUCCESS;
}
