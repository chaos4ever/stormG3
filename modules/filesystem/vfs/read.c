/* $chaos: read.c,v 1.1 2002/08/04 09:27:19 per Exp $ */
/* Abstract: vfs_read () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "vfs.h"

/* Read from a file. */
return_t vfs_read (vfs_file_handle_t handle, void *buffer, 
                   size_t length)
{
    file_t *file = find_file (handle);

    return_t return_value = file->mount->filesystem.read (handle, buffer, length);
    return return_value;
}
