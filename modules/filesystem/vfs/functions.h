/* $chaos: functions.h,v 1.1 2002/08/04 09:27:18 per Exp $ */
/* Abstract: VFS module functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/* Make sure the virtual path given is of the right format --
   //something */
bool is_virtual (char *path);

/* Make sure the logical path given is of the right format --
   /something. */
bool is_logical (char *path);

/* Find the filesystem for a file name. */
assign_t *find_filesystem (char *filename);

/* Find the file with the given handle. */
file_t *find_file (vfs_file_handle_t handle);

/* Find a free file handle. */
vfs_file_handle_t find_free_handle (void);

/* Find the mounted file system with the given mount point. */
mount_t *find_mount (char *virtual);

/* Normalize a file name (remove the mount part). */
char *normalize (assign_t *assign, char *filename);

/* Open a file. */
return_t vfs_open (char *filename, vfs_file_mode_t mode, 
                   vfs_file_handle_t *handle);

/* Close a file. */
return_t vfs_close (vfs_file_handle_t handle);

/* Mount the given block device into the given path. */
return_t vfs_mount (char *path, block_service_t *block);

/* Assign a virtual path to a logical. */
return_t vfs_assign (char *virtual, char *logical);

/* Read from a file. */
return_t vfs_read (vfs_file_handle_t handle, void *buffer, 
                   size_t length);

/* Get information about a file. */
return_t vfs_info (char *path, vfs_file_info_t *info);

#endif /* !__FUNCTIONS_H__ */
