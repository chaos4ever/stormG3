/* $chaos: capability.h,v 1.3 2002/10/24 21:37:22 per Exp $ */
/* Abstract: Capabilities support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                capability.h
 * @brief               Capabilities support.
 */

#ifndef __STORM_IA32_CAPABILITY_H__
#define __STORM_IA32_CAPABILITY_H__

/**
 * @brief               The name of the kernel capability class.
 */
#define CAPABILITY_CLASS_KERNEL \
                        "kernel"

/**
 * @brief               The name of the super user capability.
 */
#define CAPABILITY_SUPER_USER \
                        "super_user"

/**
 * @brief               Clone all the capabilities from one capability
 *                      list to another.
 * @param target        Double pointer to the target capability list.
 * @param source        Pointer to the source capability list.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t         capability_clone (capability_t **target,
                                          capability_t *source);

#endif /* !__STORM_IA32_CAPABILITY_H__ */
