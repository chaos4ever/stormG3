/* $chaos: kernel.h,v 1.1 2002/12/02 20:47:32 per Exp $ */
/* Abstract: Definition of the kernel protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             kernel.h
 * @brief            Definition of the kernel protocol.
 */

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
