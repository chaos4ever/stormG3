/* $chaos: functions.h,v 1.1 2002/12/17 21:48:13 per Exp $ */
/* Abstract: Kernel library functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             kernel/functions.h
 * @brief            Kernel library functions.
 */

#ifndef __LIBRARY_KERNEL_FUNCTIONS_H__
#define __LIBRARY_KERNEL_FUNCTIONS_H__

/**
 * @brief               Handy function for connecting to the first
 *                      available kernel service.
 * @param kernel        Pointer to a structure where the connection
 *                      information will be stored.
 * @return              KERNEL_RETURN_SUCCESS if successful.
 */
extern return_t kernel_init (kernel_service_t *kernel);

#endif /* !__LIBRARY_KERNEL_FUNCTIONS_H__ */
