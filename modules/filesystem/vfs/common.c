/* $chaos: common.c,v 1.2 2002/08/11 18:34:07 per Exp $ */
/* Abstract: Common helper functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* Make sure the virtual path given is of the right format. It needs
   to be //something, where something is a string consisting of only
   characters acceptable for a path. */

#include "vfs.h"

/* Make sure the virtual path given is of the right format --
   //something */
bool is_virtual (char *path)
{
    // FIXME: Perform checks.
    path = NULL;
    return TRUE;
}

/* Make sure the logical path given is of the right format --
   /something. */
bool is_logical (char *path)
{
    // FIXME: Perform checks.
    path = NULL;
    return TRUE;
}

/* Find the mounted file system with the given mount point. */
mount_t *find_mount (char *virtual)
{
    mount_t *mount = first_mount;

    while (mount != NULL)
    {
        if (string_compare (mount->path, virtual) == 0)
        {
            return mount;
        }
        mount = (mount_t *) mount->next;
    }
    
    return NULL;
}

/* Find the filesystem for a file name. */
assign_t *find_filesystem (char *filename)
{
    assign_t *assign = first_assign;

    while (assign != NULL)
    {
        /* Skip the root for now, try it out later. */
        if (string_compare (assign->logical_path, "/") == 0)
        {
            assign = (assign_t *) assign->next;
            continue;
        }

#ifdef DEBUG
        debug_print ("%s %s\n", assign->logical_path, filename);
#endif
        if (string_compare_max (assign->logical_path, filename, string_length (assign->logical_path)) == 0)
        {
            return assign;
        }
        assign = (assign_t *) assign->next;
    }
    
    /* Could it be in the root. */    
    assign = first_assign;
    while (assign != NULL)
    {
#ifdef DEBUG
        debug_print ("%s %s\n", assign->logical_path, filename);
#endif
        if (string_compare_max (assign->logical_path, filename, string_length (assign->logical_path)) == 0)
        {
            return assign;
        }
        assign = (assign_t *) assign->next;
    }

    return NULL;
}

/* Find the file with the given handle. */
file_t *find_file (vfs_file_handle_t handle)
{
    file_t *file = first_file;

    while (file != NULL)
    {
        if (file->handle == handle)
        {
            return file;
        }
        file = (file_t *) file->next;
    }

    /* No file with the given handle found. */
    return NULL;
}

/* Find a free file handle. */
vfs_file_handle_t find_free_handle (void)
{
    free_handle++;
    return free_handle - 1;
}

/* Normalize a file name (remove the mount part). */
char *normalize (assign_t *assign, char *filename)
{
    size_t strip_length = string_length (assign->logical_path);

    /* Make sure the file name is long enough. */
    if (strip_length > string_length (filename))
    {
        return NULL;
    }

    return &filename[strip_length];
}
