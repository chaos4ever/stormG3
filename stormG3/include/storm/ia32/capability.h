/* $chaos: dotfile.emacs,v 1.37 2002/10/14 16:03:33 per Exp $ */
/* Abstract: Capabilities support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             capability.h
 * @brief            Capabilities support.
 */

#ifndef __STORM_IA32_CAPABILITY_H__
#define __STORM_IA32_CAPABILITY_H__

/**
 * @brief               The length of a capability ID.
 */
#define CAPABILITY_ID_LENGTH \
                        32

/**
 * @brief               A capability.
 */
typedef struct
{
    /**
     * @brief           The capability ID.
     */
    char                id[CAPABILITY_ID_LENGTH];

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
