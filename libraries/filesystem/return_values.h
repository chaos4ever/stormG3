/* $chaos: return_values.h,v 1.1 2002/07/21 12:38:40 per Exp $ */
/* Abstract: Return values returned by the filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __FILESYSTEM_RETURN_VALUES_H__
#define __FILESYSTEM_RETURN_VALUES_H__

enum
{
    /* The function returned successfully. */
    FILESYSTEM_RETURN_SUCCESS,

    /* The service was not available. */
    FILESYSTEM_RETURN_SERVICE_UNAVAILABLE
};

#endif /* !__FILESYSTEM_RETURN_VALUES_H__ */
