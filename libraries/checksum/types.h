/* $chaos: types.h,v 1.3 2002/05/23 11:14:25 per Exp $ */
/* Abstract: Checksum library types. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_CHECKSUM_TYPES_H__
#define __LIBRARY_CHECKSUM_TYPES_H__

#include <storm/storm.h>

/* Type definitions. */
/* MD5 context. */
typedef struct
{
    /* State (ABCD). */
    uint32_t state[4];
    
    /* Number of bits, modulo 2^64 (lsb first). */
    uint32_t count[2];
    
    /* Input buffer. */
    unsigned char buffer[64];
} checksum_md5_context_type;

typedef char checksum_md5_digest_type[CHECKSUM_MD5_DIGEST_LENGTH];

#endif /* !__LIBRARY_CHECKSUM_TYPES_H__ */
