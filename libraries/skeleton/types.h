/* $chaos: types.h,v 1.5 2002/10/04 19:00:57 per Exp $ */
/* Abstract: Types used by the virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VFS_TYPES_H__
#define __VFS_TYPES_H__

#include <block/block.h>

/* A file handle. */
typedef int vfs_file_handle_t;

/* A file mode. File modes are defined in vfs/defines.h. */
typedef int vfs_file_mode_t;

/* A file info structure, used for returning file information. */
typedef struct
{
    /* Size of the file. */
    size_t size;
} vfs_file_info_t;

typedef return_t (*vfs_mount_t)(char *path, block_service_t *block);
typedef return_t (*vfs_assign_t)(char *virtual_path, char *logical_path);
typedef return_t (*vfs_open_t)(char *filename, vfs_file_mode_t file_mode, 
                               vfs_file_handle_t *handle);
typedef return_t (*vfs_close_t)(vfs_file_handle_t handle);
typedef return_t (*vfs_read_t)(vfs_file_handle_t handle, void *buf, 
                               size_t length);
typedef return_t (*vfs_info_t)(char *path, vfs_file_info_t *info);
// FIXME: Implement the following.
typedef return_t (*vfs_write_t)(vfs_file_handle_t handle, void *buf,
                                size_t length);
typedef return_t (*vfs_seek_t)(vfs_file_handle_t handle, size_t offset, 
                               int whence);

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

    /* Mount the given block device at the given virtual mount point. */
    vfs_mount_t mount;

    /* Assign a virtual path to the logical tree. */
    vfs_assign_t assign;

    /* Open a file. */
    vfs_open_t open;

    /* Close a file. */
    vfs_close_t close;

    /* Read from a file. */
    vfs_read_t read;

    /* Get information about a file. */
    vfs_info_t info;

    /* Set the location in a file. */
    vfs_seek_t seek;

    // TODO:
    /* Return the location in a file. */
    /* Write to a file. */
    /* Read from a directory. */
} vfs_service_t;

#endif /* !__VFS_TYPES_H__ */
