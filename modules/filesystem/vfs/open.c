/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: vfs_open () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "vfs.h"

/* Open a file. */
return_t vfs_open (char *filename, vfs_file_mode_t mode, 
                   vfs_file_handle_t *handle) 
{
    file_t *new_file;
    return_t return_value;

    /* Find out which filesystem this file is located on. */
    assign_t *assign = find_filesystem (filename);
    if (assign == NULL || assign->mount == NULL)
    {
        debug_print ("Not found");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Strip the volume path from our filename. */
    filename = normalize (assign, filename);

    /* This does the real opening (checking of permissions etc). */
    return_value = assign->mount->filesystem.open (filename, mode, handle); 
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = memory_global_allocate ((void **) &new_file, sizeof (file_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Add this file to our data structure. */
    // FIXME: Locking from here...
    new_file->next = (struct file_t *) first_file;
    new_file->handle = find_free_handle ();
    new_file->mount = assign->mount;
    string_copy_max (new_file->filename, filename, PATH_MAX);
    first_file = new_file;
    // FIXME: ...to here.

    /* Find a free handle. */
    *handle = new_file->handle;
    
    return STORM_RETURN_SUCCESS;
}

