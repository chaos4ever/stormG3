/* $chaos: functions.h,v 1.4 2002/11/20 20:02:53 per Exp $ */
/* Abstract: Function definitions used by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __FILESYSTEM_FUNCTIONS_H__
#define __FILESYSTEM_FUNCTIONS_H__

/* Lookup the first filesystem service provider. */
extern return_t filesystem_lookup (filesystem_service_t *filesystem);

/* Register a filesystem service provider. */
extern return_t filesystem_register (service_register_t *service_register_info,
                                     service_method_t *service_method);

#endif /* !__FILESYSTEM_FUNCTIONS_H__ */
