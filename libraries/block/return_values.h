/* $chaos: return_values.h,v 1.1 2002/07/06 08:29:46 per Exp $ */
/* Abstract: Return values returned by the block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __BLOCK_RETURN_VALUES_H__
#define __BLOCK_RETURN_VALUES_H__

enum
{
    /* The function returnes successfully. */
    BLOCK_RETURN_SUCCESS,

    /* The service was not available. */
    BLOCK_RETURN_SERVICE_UNAVAILABLE
};

#endif /* !__BLOCK_RETURN_VALUES_H__ */
