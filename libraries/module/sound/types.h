/* $chaos: types.h,v 1.2 2002/11/21 21:49:14 per Exp $ */
/* Abstract: Sound library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __SOUND_TYPES_H__
#define __SOUND_TYPES_H__

typedef struct
{
    /* The sound magic cookie. */
    unsigned int magic_cookie;
} sound_service_t;

#endif /* !__SOUND_TYPES_H__ */
