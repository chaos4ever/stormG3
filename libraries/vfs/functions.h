/* $chaos: functions.h,v 1.3 2002/08/09 05:59:42 per Exp $ */
/* Abstract: Function definitions used by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VFS_FUNCTIONS_H__
#define __VFS_FUNCTIONS_H__

/* Lookup the first virtual filesystem service provider. */
extern return_t vfs_lookup (vfs_service_t *vfs);

/* Register a VFS service provider. */
extern return_t vfs_register (service_register_t *service_register_info,
                              service_method_t *service_method);

#endif /* !__VFS_FUNCTIONS_H__ */
