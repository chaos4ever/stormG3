/* $chaos: return_values.h,v 1.1 2002/07/21 12:55:51 per Exp $ */
/* Abstract: Return values returned by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VIRTUAL_FILESYSTEM_RETURN_VALUES_H__
#define __VIRTUAL_FILESYSTEM_RETURN_VALUES_H__

enum
{
    /* The function returned successfully. */
    VIRTUAL_FILESYSTEM_RETURN_SUCCESS,

    /* The service was not available. */
    VIRTUAL_FILESYSTEM_RETURN_SERVICE_UNAVAILABLE
};

#endif /* !__VIRTUAL_FILESYSTEM_RETURN_VALUES_H__ */
