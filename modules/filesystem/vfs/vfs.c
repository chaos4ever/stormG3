/* $chaos: virtual.c,v 1.2 2002/07/30 12:57:19 per Exp $ */
/* Abstract: Virtual file system provider. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <filesystem/filesystem.h>
#include <string/string.h>
#include <vfs/vfs.h>

#include "vfs.h"

/* A linked list of mounted filesystems. */
mount_t *first_mount = NULL;

/* A linked list of assignments. */
assign_t *first_assign = NULL;

/* A linked list of open files. */
file_t *first_file;

/* Information about our block device. */
block_info_t info;

/* The first free file handle. */
vfs_file_handle_t free_handle = 0;

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

/* Find the mounted file system with the given mount point. */
static mount_t *find_mount (char *virtual)
{
    mount_t *mount = first_mount;

    while (mount != NULL)
    {
        if (string_compare (mount->path, virtual) == 0)
        {
            return mount;
        }
        mount = (mount_t *) mount->next;
    }
    
    return NULL;
}

/* Find the filesystem for a file name. */
static mount_t *find_filesystem (char *filename)
{
    assign_t *assign = first_assign;

    while (assign != NULL)
    {
        if (string_compare (assign->logical_path, filename) == 0)
        {
            return assign->mount;
        }
        assign = (assign_t *) assign->next;
    }

    return NULL;
}

/* Find a free file handle. */
static vfs_file_handle_t find_free_handle (void)
{
    free_handle++;
    return free_handle - 1;
}

/* Mount the given block device into the given path. */
static return_t vfs_mount (char *path, block_service_t *block)
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

/* Assign a directory in the virtual file system (with the root as //)
   into the logical file system (with the root /). */
static return_t vfs_assign (char *virtual, char *logical)
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

/* Open a file. */
static return_t vfs_open (char *filename, vfs_file_mode_t mode, 
                          vfs_file_handle_t *handle) 
{
    file_t *new_file;

    /* Find out which filesystem this file is located on. */
    mount_t *mount = find_filesystem (filename);
    if (mount != NULL)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    // FIXME: Check if we have permission to do this.
    // FIXME: Support writing to files.
    mode = 0;

    // FIXME: Strip the volume path (/mnt/whatever) from our filename.
    // mount->filesystem.open (filename, mode, ...); 

    return_t return_value = memory_global_allocate ((void **) &new_file, sizeof (file_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Add this file to our data structure. */
    // FIXME: Locking from here...
    new_file->next = (struct *file_t) first_file;
    new_file->handle = find_free_handle ();
    new_file->mount = mount;
    string_copy_max (new_file->filename, filename, PATH_MAX);
    first_file = new_file;
    // FIXME: ...to here.

    /* Find a free handle. */
    *handle = new_file->handle;
    
    return STORM_RETURN_SUCCESS;
}

/* Close a file. */
static return_t vfs_close (vfs_file_handle_t handle)
{
    // FIXME: Remove this file handle from the data structures and so
    // on.
    handle = -1;
    return STORM_RETURN_SUCCESS;
}

/* Read from a file. */
static return_t vfs_read (vfs_file_handle_t handle, void *buffer, 
                          size_t length)
{
    handle = -1;
    buffer = NULL;
    length = 0;
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Return some information about the filesystem service (function pointers to
   our functionality). */
static return_t service_info (void *vfs_void)
{
    vfs_service_t *vfs = (vfs_service_t *) vfs_void;
    vfs->magic_cookie = VFS_COOKIE;
    vfs->mount = vfs_mount;
    vfs->assign = vfs_assign;
    vfs->open = vfs_open;
    vfs->close = vfs_close;
    vfs->read = vfs_read;
    return STORM_RETURN_SUCCESS;
}


int module_start (void)
{
    // FIXME: Use vfs_register
    return service_register ("vfs", "chaos development",
                             "VFS module", "1",
                             VFS_SERVICE_VERSION,
                             &service_info);
}
