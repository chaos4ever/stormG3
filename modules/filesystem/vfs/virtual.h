/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Virtual file system provider, header file. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VIRTUAL_H__
#define __VIRTUAL_H__

/* The maximum length of a path of this style: //cdrom. */
#define VIRTUAL_PATH_MAX                128

/* The maximum length of a path of this style: /mounted/cdrom. (The
   maximum only applies to mount points, not ordinary files) */
#define LOGICAL_PATH_MAX                256

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

typedef struct
{
    /* A pointer to the next entry in the list. */
    struct assign_t *next;

    /* The path name in the virtual file tree of this file system. */
    char virtual_path[VIRTUAL_PATH_MAX];

    /* The path name in the logical file tree of this file system. */
    char logical_path[LOGICAL_PATH_MAX];
} assign_t;

#endif /* !__VIRTUAL_H__ */
