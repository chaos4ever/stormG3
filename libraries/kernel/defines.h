/* $chaos: defines.h,v 1.1 2002/10/29 20:46:21 per Exp $ */
/* Abstract: Definitions used by the kernel library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KERNEL_DEFINES_H__
#define __KERNEL_DEFINES_H__

/* The major version of the kernel service. */
#define KERNEL_SERVICE_MAJOR_VERSION \
                        (0)

/* The minor version of the kernel service. */
#define KERNEL_SERVICE_MINOR_VERSION \
                        (1)

/* Kernel functions. */
enum kernel_function_t
{
    /* Write something to the kernel log. */
    KERNEL_FUNCTION_LOG,
};

#endif /* !__KERNEL_DEFINES_H__ */
