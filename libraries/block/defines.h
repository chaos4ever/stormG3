/* $chaos: defines.h,v 1.1 2002/07/21 12:31:37 per Exp $ */
/* Abstract: Block library defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __BLOCK_DEFINES_H__
#define __BLOCK_DEFINES_H__

/* A magic cookie, to make sure this is really a block service
   provider. FIXME: Let this be truly unique. */
#define BLOCK_MAGIC_COOKIE              0x12345678

/* The version of the block service. */
#define BLOCK_SERVICE_VERSION           1

#endif /* !__BLOCK_DEFINES_H__ */
