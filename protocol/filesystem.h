/* $chaos: $ */
/* Abstract: Definitions for the filesystem protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             filesystem.h
 * @brief            Definition of the filesystem protocol.
 */

#ifndef __PROTOCOL_FILESYSTEM_H__
#define __PROTOCOL_FILESYSTEM_H__

/* A magic cookie, to make sure this is really a filesystem service
   provider. FIXME: Let this be truly unique. */
#define FILESYSTEM_MAGIC_COOKIE              0x12345678

/* The major version of the block service. Bump this one step when you
   make CHANGES to the block service API that will make it
   incompatible with old programs. */
#define FILESYSTEM_PROTOCOL_MAJOR_VERSION \
                        (0)

/* The minor version of the block service. Should be bumped whenever a
   function is added to the API that DOES NOT break the binary
   compatibility with previously compiled programs. */
#define FILESYSTEM_PROTOCOL_MINOR_VERSION \
                        (1)

#endif /* !__PROTOCOL_FILESYSTEM_H__ */
