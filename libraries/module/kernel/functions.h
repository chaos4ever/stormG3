/* $chaos: functions.h,v 1.2 2002/11/20 20:05:38 per Exp $ */
/* Abstract: Functions in the kernel library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KERNEL_FUNCTIONS_H__
#define __KERNEL_FUNCTIONS_H__

/* Lookup the first kernel service provider. */
extern return_t kernel_lookup (kernel_service_t *kernel);

/* Register a kernel service provider. */
extern return_t kernel_register (service_register_t *service_register_info,
                                 service_method_t *method);

#endif /* !__KERNEL_FUNCTIONS_H__ */
