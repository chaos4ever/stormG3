/* $chaos: functions.h,v 1.4 2002/11/20 20:03:44 per Exp $ */
/* Abstract: Function definitions for the block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __BLOCK_FUNCTIONS_H__
#define __BLOCK_FUNCTIONS_H__

/* Lookup the first block service provider. */
extern return_t block_lookup (block_service_t *block);

/* Register a block service provider. */
extern return_t block_register (service_register_t *service_register_info,
                                service_method_t *service_method);

#endif /* !__BLOCK_FUNCTIONS_H__ */
