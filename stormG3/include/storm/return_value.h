/* $chaos: return_value.h,v 1.8 2002/10/10 15:26:21 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                return_value.h
 * @brief               Return values.
 */

#ifndef __STORM_RETURN_VALUES_H__
#define __STORM_RETURN_VALUES_H__

/**
 * @brief               A return value.
 */
enum return_t 
{
    /**
     * @brief           The call succeeded. 
     */
    STORM_RETURN_SUCCESS = 0,

    /**
     * @brief           The function requested has not been implemented. 
     */
    STORM_RETURN_NOT_IMPLEMENTED,

    /**
     * @brief           There is no free memory in the system.
     */
    STORM_RETURN_OUT_OF_MEMORY,

    /**
     * @brief           One of the internal data structures was broken. 
     *                  This error is most likely caused by kernel bugs.
     */
    STORM_RETURN_INTERNAL_DATA_ERROR,
    
    /**
     * @brief           The module that we tried to load was invalid in some
     *                  way. 
     */
    STORM_RETURN_MODULE_INVALID,

    /**
     * @brief           The resource we attempted to use was busy. 
     */
    STORM_RETURN_BUSY,

    /**
     * @brief           A kernel function was passed an invalid argument. 
     */
    STORM_RETURN_INVALID_ARGUMENT,

    /**
     * @brief           The requested entity was not found. 
     */
    STORM_RETURN_NOT_FOUND
};

#endif /* !__STORM_RETURN_VALUES_H__ */
