/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: vfs_close () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "vfs.h"

/* Close a file. */
return_t vfs_close (vfs_file_handle_t handle)
{
    // FIXME: Remove this file handle from the data structures and so
    // on.
    handle = -1;
    return STORM_RETURN_SUCCESS;
}
