/* $chaos: types.h,v 1.1 2002/07/21 12:38:40 per Exp $ */
/* Abstract: Types used by the virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VIRTUAL_FILESYSTEM_TYPES_H__
#define __VIRTUAL_FILESYSTEM_TYPES_H__

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

} virtual_filesystem_service_t;

#endif /* !__VIRTUAL_FILESYSTEM_TYPES_H__ */
