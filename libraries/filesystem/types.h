/* $chaos: types.h,v 1.1 2002/07/21 12:38:40 per Exp $ */
/* Abstract: Types used by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __FILESYSTEM_TYPES_H__
#define __FILESYSTEM_TYPES_H__

#include <block/block.h>

typedef return_t (*filesystem_mount_t)(block_service_t *block);

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

    /* Mount a volume. */
    filesystem_mount_t mount;
} filesystem_service_t;

#endif /* !__FILESYSTEM_TYPES_H__ */
