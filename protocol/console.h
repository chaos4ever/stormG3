/* $chaos: console.h,v 1.1 2002/12/03 14:11:59 johannes Exp $ */
/* Abstract: Definitions for the console protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             console.h
 * @brief            Definition of the console protocol.
 */

#ifndef __PROTOCOL_CONSOLE_H__
#define __PROTOCOL_CONSOLE_H__

/* A magic cookie, to make sure this is really a console service
   provider. FIXME: Let this be truly unique. */
#define CONSOLE_MAGIC_COOKIE              0x12345678

/* The major version of the block service. Bump this one step when you
   make CHANGES to the block service API that will make it
   incompatible with old programs. */
#define CONSOLE_PROTOCOL_MAJOR_VERSION \
                        (0)

/* The minor version of the block service. Should be bumped whenever a
   function is added to the API that DOES NOT break the binary
   compatibility with previously compiled programs. */
#define CONSOLE_PROTOCOL_MINOR_VERSION \
                        (1)

#endif /* !__PROTOCOL_CONSOLE_H__ */
