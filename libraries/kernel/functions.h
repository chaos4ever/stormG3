/* $chaos: functions.h,v 1.2 2002/10/04 21:23:56 per Exp $ */
/* Abstract: Functions in the kernel library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KERNEL_FUNCTIONS_H__
#define __KERNEL_FUNCTIONS_H__

/* Lookup the first kernel service provider. */
extern return_t kernel_lookup (kernel_service_t *kernel);

/* Register a kernel service provider. */
extern return_t kernel_register (char *vendor, char *model, char *id,
                                 service_info_t service_info);

#endif /* !__KERNEL_FUNCTIONS_H__ */
