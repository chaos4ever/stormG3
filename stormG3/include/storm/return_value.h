/* $chaos: return_value.h,v 1.3 2002/06/15 22:39:17 per Exp $ */
/* Abstract: Return values. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_RETURN_VALUES_H__
#define __STORM_RETURN_VALUES_H__

enum {
    /* The call succeeded. */
    STORM_RETURN_SUCCESS = 0,

    /* Function not implemented. */
    STORM_RETURN_NOT_IMPLEMENTED,

    /* The system is out of memory. */
    STORM_RETURN_OUT_OF_MEMORY,

    /* One of the internal data structures was broken. */
    STORM_RETURN_INTERNAL_DATA_ERROR,
    
    /* The module was invalid in some way. */
    STORM_RETURN_MODULE_INVALID,

    /* The resource we attempted to use was busy. */
    STORM_RETURN_BUSY,

    /* A kernel function was passed an invalid argument. */
    STORM_RETURN_INVALID_ARGUMENT
};

#endif /* !__STORM_RETURN_VALUES_H__ */
