/* $chaos: defines.h,v 1.2 2002/10/04 19:00:50 per Exp $ */
/* Abstract: Block library defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __BLOCK_DEFINES_H__
#define __BLOCK_DEFINES_H__

/* A magic cookie, to make sure this is really a block service
   provider. FIXME: Let this be truly unique. */
#define BLOCK_MAGIC_COOKIE              0x12345678

/* The major version of the block service. Bump this one step when you
   make CHANGES to the block service API that will make it
   incompatible with old programs. */
#define BLOCK_SERVICE_MAJOR_VERSION \
                        (0)

/* The minor version of the block service. Should be bumped whenever a
   function is added to the API that DOES NOT break the binary
   compatibility with previously compiled programs. */
#define BLOCK_SERVICE_MINOR_VERSION \
                        (1)

#endif /* !__BLOCK_DEFINES_H__ */
