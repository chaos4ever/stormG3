/* $chaos: types.h,v 1.1 2002/07/28 19:25:31 per Exp $ */
/* Abstract: Types used by the virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VFS_TYPES_H__
#define __VFS_TYPES_H__

#include <block/block.h>

/* A file handle. */
typedef int vfs_file_handle_t;

typedef return_t (*vfs_mount_t)(char *path, block_service_t *block);
typedef return_t (*vfs_assign_t)(char *virtual_path, char *logical_path);
typedef return_t (*vfs_open_t)(char *filename, vfs_file_handle_t *handle);
typedef return_t (*vfs_close_t)(vfs_file_handle_t handle);

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

    // TODO:
    /* 'stat' a file. */
    /* Set the location in a file. */
    /* Return the location in a file. */
    /* Read from a file. */
    /* Write to a file. */
    /* Read from a directory. */
} vfs_service_t;

#endif /* !__VFS_TYPES_H__ */
