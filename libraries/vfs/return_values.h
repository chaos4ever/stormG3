/* $chaos: return_values.h,v 1.1 2002/07/28 19:25:31 per Exp $ */
/* Abstract: Return values returned by the virtual filesystem
   library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

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
