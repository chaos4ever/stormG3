/* $chaos: functions.h,v 1.3 2002/05/23 11:14:25 per Exp $ */
/* Abstract: CRC32 library function prototypes. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_CHECKSUM_FUNCTIONS_H__
#define __LIBRARY_CHECKSUM_FUNCTIONS_H__

#include <storm/storm.h>

extern return_t checksum_crc32 (uint8_t *block, unsigned int length,
                                uint32_t *result);
extern return_t checksum_md5 (void *input, unsigned int length,
                              checksum_md5_digest_type *digest);

#endif /* !__LIBRARY_CHECKSUM_FUNCTIONS_H__ */
