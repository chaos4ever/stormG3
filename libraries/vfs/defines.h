/* $chaos: defines.h,v 1.2 2002/07/28 19:30:54 per Exp $ */
/* Abstract: Defines used by the virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VFS_DEFINES_H__
#define __VFS_DEFINES_H__

/* Defines. */
// FIXME: This should be unique.
#define VFS_COOKIE                      0x12345678

/* The version of the virtual filesystem service that we are using. */
#define VFS_SERVICE_VERSION             1

enum
{
    /* Open the file for reading. */
    VFS_FILE_MODE_READ,

    /* Open the file for writing. */
    VFS_FILE_MODE_WRITE

    /* ...and so on... */
};

#endif /* !__VFS_DEFINES_H__ */
