/* $chaos: capability.h,v 1.1 2002/10/17 21:28:37 per Exp $ */
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
 * @brief               The length of a capability ID.
 */
#define CAPABILITY_CLASS_LENGTH \
                        (16)

/**
 * @brief               The length of a capability name.
 */
#define CAPABILITY_NAME_LENGTH \
                        (32)

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
 * @brief               A capability.
 *
 * We could eventually move this to a more advanced data structure
 * where the capability_list is rather a list of the capability
 * classes, and the capability classes hold a list of all the
 * capabilities in this class.
 */
typedef struct
{
    /**
     * @brief           The capability ID.
     */
    char                class[CAPABILITY_CLASS_LENGTH];

    /**
     * @brief           The capability name (must be unique).
     */
    char                name[CAPABILITY_CLASS_LENGTH];

    /**
     * @brief           Pointer to the previous capability.
     */
    struct capability_t *previous;

    /**
     * @brief           Pointer to the next capability.
     */
    struct capability_t *next;
} capability_t;

#endif /* !__STORM_IA32_CAPABILITY_H__ */
