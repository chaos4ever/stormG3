/* $chaos: types.h,v 1.2 2002/07/29 07:11:20 per Exp $ */
/* Abstract: Types used by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __FILESYSTEM_TYPES_H__
#define __FILESYSTEM_TYPES_H__

#include <block/block.h>
#include <vfs/vfs.h>

typedef return_t (*filesystem_mount_t)(block_service_t *block);
typedef return_t (*filesystem_open_t)(char *filename, vfs_file_mode_t mode, vfs_file_handle_t *handle);
typedef return_t (*filesystem_close_t)(vfs_file_handle_t handle);
typedef return_t (*filesystem_read_t)(vfs_file_handle_t handle, void *buffer, size_t count);

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

    /* Mount a volume. */
    filesystem_mount_t mount;

    /* Open a file. */
    filesystem_open_t open;

    /* Close a file. */
    filesystem_close_t close;

    /* Read from a file. */
    filesystem_read_t read;

    // TODO:
    /* Write to a file. */
} filesystem_service_t;

#endif /* !__FILESYSTEM_TYPES_H__ */
