/* $chaos: virtual.h,v 1.1 2002/07/28 19:23:43 per Exp $ */
/* Abstract: Virtual file system provider, header file. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VFS_H__
#define __VFS_H__

/* The maximum length of a path of this style: //cdrom. */
#define VIRTUAL_PATH_MAX                128

/* The maximum length of a path of this style: /mounted/cdrom. (The
   maximum only applies to mount points, not ordinary files) */
#define LOGICAL_PATH_MAX                256

/* The maximum length of a file name, relative to the filesystem
   root. */
#define PATH_MAX                        1024

/* A mounted filesystem. */
typedef struct
{
    /* A pointer to the next entry in the list. */
    struct mount_t *next;

    /* The path name in the virtual file tree where this file system
       is mounted. */
    char path[VIRTUAL_PATH_MAX];
    
    /* The block service that we have mounted at this location. */
    block_service_t block;

    /* The filesystem that this volume is using. */
    filesystem_service_t filesystem;
} mount_t;

/* An assignment -- like / -> // or /mnt/spam -> //spam */
typedef struct
{
    /* A pointer to the next entry in the list. */
    struct assign_t *next;

    /* The path name in the virtual file tree of this file system. */
    char virtual_path[VIRTUAL_PATH_MAX];

    /* The path name in the logical file tree of this file system. */
    char logical_path[LOGICAL_PATH_MAX];

    /* The mount structure of this filesystem. */
    mount_t *mount;
} assign_t;

/* An open file -- used for resolving a file descriptor number. */
typedef struct
{
    /* A pointer to the next file. */
    struct file_t *next;

    /* The file handle. */
    vfs_file_handle_t handle;

    /* The filesystem the file is located on. */
    mount_t *mount;

    /* The file name, relative to the logical root. */
    char filename[PATH_MAX];
} file_t;

#endif /* !__VFS_H__ */
