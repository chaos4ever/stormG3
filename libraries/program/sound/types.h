/* $chaos: types.h,v 1.1 2002/12/12 22:06:01 per Exp $ */
/* Abstract: Sound library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_SOUND_TYPES_H__
#define __LIBRARY_SOUND_TYPES_H__

typedef struct
{
    /**
     * @brief           The sound protocol magic cookie. 
     */
    unsigned int magic_cookie;
} sound_service_t;

#endif /* !__LIBRARY_SOUND_TYPES_H__ */
