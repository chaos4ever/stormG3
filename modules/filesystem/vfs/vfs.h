/* $chaos: vfs.h,v 1.3 2002/08/11 18:32:53 per Exp $ */
/* Abstract: Virtual file system provider, header file. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VFS_H__
#define __VFS_H__

#include <storm/storm.h>
#include <block/block.h>
#include <filesystem/filesystem.h>
#include <string/string.h>
#include <vfs/vfs.h>

#include "defines.h"
#include "types.h"
#include "functions.h"

/* External variables. FIXME: Move these to a separate header file. */
extern mount_t *first_mount;
extern assign_t *first_assign;
extern file_t *first_file;
extern block_info_t block_info;
extern vfs_file_handle_t free_handle;

#endif /* !__VFS_H__ */
