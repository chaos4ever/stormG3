/* $chaos: defines.h,v 1.3 2002/11/20 20:05:38 per Exp $ */
/* Abstract: Definitions used by the kernel library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __PROTOCOL_KERNEL_H__
#define __PROTOCOL_KERNEL_H__

/**
 * @brief               The major version of the kernel protocol. 
 */
#define KERNEL_PROTOCOL_MAJOR_VERSION \
                        (0)

/**
 * @brief               The minor version of the kernel protocol.
 */
#define KERNEL_PROTOCOL_MINOR_VERSION \
                        (1)

/**
 * @brief               Kernel functions. 
 */
enum kernel_function_t
{
    /**
     * @brief           Write something to the kernel log. 
     */
    KERNEL_FUNCTION_LOG,
};

#endif /* !__PROTOCOL_KERNEL_H__ */
