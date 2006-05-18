/* $chaos: vfs.c,v 1.6 2002/11/21 21:48:09 per Exp $ */
/* Abstract: Virtual file system provider. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "vfs.h"

/* A linked list of mounted filesystems. */
mount_t *first_mount = NULL;

/* A linked list of assignments. */
assign_t *first_assign = NULL;

/* A linked list of open files. */
file_t *first_file;

/* Information about our block device. */
block_info_t block_info;

/* The first free file handle. */
vfs_file_handle_t free_handle = 0;

/* Return some information about the filesystem service (function pointers to
   our functionality). */
static return_t service_info (void *vfs_void)
{
    vfs_service_t *vfs = (vfs_service_t *) vfs_void;
    vfs->magic_cookie = VFS_COOKIE;
    vfs->mount = vfs_mount;
    vfs->assign = vfs_assign;
    vfs->open = vfs_open;
    vfs->close = vfs_close;
    vfs->read = vfs_read;
    vfs->info = vfs_info;
    return STORM_RETURN_SUCCESS;
}


int module_start (void)
{
    // Something is severely broken in the ELF loader. This is set to
    // NULL above. It is put into the .data section. Still, it aint 0
    // when we first start...
    debug_print("first: %x\n", first_assign);
    first_assign = NULL;

    service_register_t service_register_info;
    service_register_info.service_vendor = "chaos development";
    service_register_info.model = "VFS module";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &service_info;

    // FIXME: Fill in this structure.
    service_method_t service_method[] =
        {
            { -1, NULL }
        };

    return vfs_register (&service_register_info, service_method);
}
