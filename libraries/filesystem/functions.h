/* $chaos: functions.h,v 1.1 2002/07/09 08:39:44 per Exp $ */
/* Abstract: Function definitions used by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __FILESYSTEM_FUNCTIONS_H__
#define __FILESYSTEM_FUNCTIONS_H__

/* Resolve the first filesystem service provider. */
extern return_t filesystem_resolve (filesystem_service_t *filesystem);

#endif /* !__FILESYSTEM_FUNCTIONS_H__ */
