/* $chaos: defines.h,v 1.1 2002/08/04 09:27:18 per Exp $ */
/* Abstract: VFS module defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* The maximum length of a path of this style: //cdrom. */
#define VIRTUAL_PATH_MAX                128

/* The maximum length of a path of this style: /mounted/cdrom. (The
   maximum only applies to mount points, not ordinary files) */
#define LOGICAL_PATH_MAX                256

/* The maximum length of a file name, relative to the filesystem
   root. */
#define PATH_MAX                        1024

#endif /* !__DEFINES_H__ */
