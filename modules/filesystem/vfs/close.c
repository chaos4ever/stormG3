/* $chaos: close.c,v 1.1 2002/08/04 09:27:18 per Exp $ */
/* Abstract: vfs_close () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "vfs.h"

/* Close a file. */
return_t vfs_close (vfs_file_handle_t handle)
{
    // FIXME: Remove this file handle from the data structures and so
    // on.
    handle = -1;
    return STORM_RETURN_SUCCESS;
}
