/* $chaos: return_values.h,v 1.2 2002/07/28 19:30:54 per Exp $ */
/* Abstract: Return values returned by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VFS_RETURN_VALUES_H__
#define __VFS_RETURN_VALUES_H__

enum
{
    /* The function returned successfully. */
    VFS_RETURN_SUCCESS,

    /* The service was not available. */
    VFS_RETURN_SERVICE_UNAVAILABLE
};

#endif /* !__VFS_RETURN_VALUES_H__ */
