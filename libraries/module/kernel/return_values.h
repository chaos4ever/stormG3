/* $chaos: return_values.h,v 1.1 2002/10/04 20:53:22 per Exp $ */
/* Abstract: Return values used by the kernel library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KERNEL_RETURN_VALUES_H__
#define __KERNEL_RETURN_VALUES_H__

enum kernel_return_t
{
    /* The function returned successfully. */
    KERNEL_RETURN_SUCCESS,

    /* No kernel service provider was found. */
    KERNEL_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__KERNEL_RETURN_VALUES_H__ */
