/* $chaos: capability.h,v 1.2 2002/10/23 21:05:07 per Exp $ */
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

#endif /* !__STORM_IA32_CAPABILITY_H__ */
