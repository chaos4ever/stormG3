/* $chaos: virtual.c,v 1.1 2002/07/24 08:10:31 per Exp $ */
/* Abstract: Virtual file system provider. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <filesystem/filesystem.h>
#include <string/string.h>
#include <virtual_filesystem/virtual_filesystem.h>

#include "virtual.h"

/* A linked list of mounted filesystems. */
mount_t *first_mount = NULL;

/* A linked list of assignments. */
assign_t *first_assign = NULL;

/* Information about our block device. */
block_info_t info;

/* Make sure the virtual path given is of the right format. It needs
   to be //something, where something is a string consisting of only
   characters acceptable for a path. */
static bool is_virtual (char *path)
{
    // FIXME: Perform checks.
    path = NULL;
    return TRUE;
}

/* Make sure the logical path given is of the right format --
   /something. */
static bool is_logical (char *path)
{
    // FIXME: Perform checks.
    path = NULL;
    return TRUE;
}

/* Mount the given block device into the given path. */
static return_t mount(char *path, block_service_t *block)
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

    block->info(&info);
    debug_print ("%u %u\n", info.block_size, info.block_count);

    return STORM_RETURN_SUCCESS;
}

/* Assign a directory in the virtual file system (with the root as //)
   into the logical file system (with the root /). */
static return_t assign(char *virtual, char *logical)
{
    assign_t *new_assign;

    if (!is_virtual (virtual))
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    if (!is_logical (logical))
    {
        return STORM_RETURN_INVALID_ARGUMENT;
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
    string_copy_max (new_assign->virtual_path, virtual, VIRTUAL_PATH_MAX);
    string_copy_max (new_assign->logical_path, logical, LOGICAL_PATH_MAX);
    first_assign = new_assign;
    // FIXME: ...to here.

    return STORM_RETURN_SUCCESS;
}

/* Open a file. */
static return_t open (char *filename, virtual_filesystem_file_handle_t *handle) {
    filename = NULL;
    *handle = -1;
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Close a file. */
static return_t close (virtual_filesystem_file_handle_t handle)
{
    handle = -1;
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Return some information about the filesystem service (function pointers to
   our functionality). */
static return_t service_info (void *virtual_filesystem_void)
{
    virtual_filesystem_service_t *virtual_filesystem = (virtual_filesystem_service_t *) virtual_filesystem_void;
    virtual_filesystem->magic_cookie = VIRTUAL_FILESYSTEM_COOKIE;
    virtual_filesystem->mount = mount;
    virtual_filesystem->assign = assign;
    virtual_filesystem->open = open;
    virtual_filesystem->close = close;
    return STORM_RETURN_SUCCESS;
}


int module_start (void)
{
    return service_register ("virtual_filesystem", "chaos development",
                             "VFS module", "1",
                             VIRTUAL_FILESYSTEM_SERVICE_VERSION,
                             &service_info);
}
