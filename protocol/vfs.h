/* $chaos: vfs.h,v 1.1 2002/12/03 14:38:03 johannes Exp $ */
/* Abstract: Definitions for the vfs protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             vfs.h
 * @brief            Definition of the vfs protocol.
 */

#ifndef __PROTOCOL_VFS_H__
#define __PROTOCOL_VFS_H__

/* A magic cookie, to make sure this is really a vfs service
   provider. FIXME: Let this be truly unique. */
#define VFS_COOKIE              0x12345678

/* The major version of the block service. Bump this one step when you
   make CHANGES to the block service API that will make it
   incompatible with old programs. */
#define VFS_PROTOCOL_MAJOR_VERSION \
                        (0)

/* The minor version of the block service. Should be bumped whenever a
   function is added to the API that DOES NOT break the binary
   compatibility with previously compiled programs. */
#define VFS_PROTOCOL_MINOR_VERSION \
                        (1)

enum vfs_file_mod_t
{
    /* Open the file for reading. */
    VFS_FILE_MODE_READ,

    /* Open the file for writing. */
    VFS_FILE_MODE_WRITE

    /* ...and so on... */
};

#endif /* !__PROTOCOL_VFS_H__ */
