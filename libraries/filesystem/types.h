/* $chaos: types.h,v 1.2 2002/07/06 08:29:22 per Exp $ */
/* Abstract: Types used by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __FILESYSTEM_TYPES_H__
#define __FILESYSTEM_TYPES_H__

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

} filesystem_service_t;

#endif /* !__FILESYSTEM_TYPES_H__ */
