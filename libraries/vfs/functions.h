/* $chaos: functions.h,v 1.1 2002/07/21 12:55:51 per Exp $ */
/* Abstract: Function definitions used by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VIRTUAL_FILESYSTEM_FUNCTIONS_H__
#define __VIRTUAL_FILESYSTEM_FUNCTIONS_H__

/* Resolve the first virtual filesystem service provider. */
extern return_t virtual_filesystem_resolve (virtual_filesystem_service_t *virtual_filesystem);

#endif /* !__VIRTUAL_FILESYSTEM_FUNCTIONS_H__ */
