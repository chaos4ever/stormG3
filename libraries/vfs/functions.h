/* $chaos: functions.h,v 1.2 2002/07/28 19:30:54 per Exp $ */
/* Abstract: Function definitions used by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VFS_FUNCTIONS_H__
#define __VFS_FUNCTIONS_H__

/* Lookup the first virtual filesystem service provider. */
extern return_t vfs_lookup (vfs_service_t *vfs);

#endif /* !__VFS_FUNCTIONS_H__ */
