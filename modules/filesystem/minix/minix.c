/* $chaos: minix.c,v 1.6 2002/08/09 06:02:35 per Exp $ */
/* Abstract: Implementation of the Minix file system. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <filesystem/filesystem.h>
#include <log/log.h>
#include <string/string.h>

#include "minix.h"

/* The log service provider that we are using. */
log_service_t log;

// FIXME: Have these dynamically allocated.
uint8_t minix_superblock_buffer[MINIX_BLOCK_SIZE];
minix_superblock_t *superblock = (minix_superblock_t *) &minix_superblock_buffer;
// FIXME: One of these for each volume mounted.
minix_fs_t fs;

uint8_t minix_buffer[MINIX_BLOCK_SIZE];
uint8_t minix_buffer2[MINIX_BLOCK_SIZE];
uint8_t read_buffer[MINIX_BLOCK_SIZE];

minix_file_t file[MINIX_OPEN_FILES];
vfs_file_handle_t free_handle = 0;

/* Get a free file handle. */
static vfs_file_handle_t minix_get_free_handle (void)
{
    free_handle++;
    if (free_handle == MINIX_OPEN_FILES)
    {
        debug_print ("Reached open file limit! Please fix in %s, %u.\n", __FILE__, __LINE__);
        while (TRUE);
    }
    return free_handle - 1;
}

/* Find an inode with the given inode number. */
static minix2_inode_t *minix2_find_inode (minix_fs_t *minix_fs, unsigned int number)
{
    unsigned int inode_block = minix_fs->inode_block + (number - 1) / MINIX2_INODE_PER_BLOCK;
    unsigned int inode_which = (number - 1) % MINIX2_INODE_PER_BLOCK;

    minix_fs->block.read ((inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, &minix_buffer2);
    return (minix2_inode_t *) (&minix_buffer2[inode_which * sizeof (minix2_inode_t)]);
}

/* Make sure this is a Minix file system and set up some structures so
   we can access it. Return TRUE if it is a valid, supported file
   system and FALSE otherwise. */
static bool minix_init (minix_fs_t *minix_fs)
{
    /* Make sure this is a valid Minix file system. */
    if (minix_fs->block.read (MINIX_SUPERBLOCK_LOCATION / minix_fs->block_size, 
                              MINIX_BLOCK_SIZE / minix_fs->block_size,
                              superblock) == 0)
    {
        if (superblock->magic == MINIX_MAGIC)
        {
            minix_fs->version = 1;
            minix_fs->name_length = MINIX_FILE_NAME_LENGTH;
        }
        else if (superblock->magic == MINIX_MAGIC_EXTENDED)
        {
            minix_fs->version = 1;
            minix_fs->name_length = MINIX_EXTENDED_FILE_NAME_LENGTH;
        }
        else if (superblock->magic == MINIX2_MAGIC)
        {
            minix_fs->version = 2;
            minix_fs->name_length = MINIX_FILE_NAME_LENGTH;
        }
        else if (superblock->magic == MINIX2_MAGIC_EXTENDED)
        {
            minix_fs->version = 2;
            minix_fs->name_length = MINIX_EXTENDED_FILE_NAME_LENGTH;
        }
        else
        {
            debug_print ("Not a valid file system.\n");
            return FALSE;
        }

        //        debug_print ("Minix file system version %d found.\n", minix_fs->version);

        if (superblock->state == 1)
        {
            //            debug_print ("Filesystem is clean.\n");
        }
        else
        {
            debug_print ("File system has errors.\n");
            return FALSE;
        }
    }
    else
    {
        debug_print ("Reading from block service failed.\n");
        return FALSE;
    }

    /* Locate the inode block. */
    minix_fs->inode_block = (2 + superblock->imap_blocks +
                             superblock->zmap_blocks);
    return TRUE;
}

/* Find a file in the root directory of a Minix v2 filesystem. */
static minix2_inode_t *minix2_find_file (minix_fs_t *minix_fs, char *filename)
{
    /* Read the root inode. */
    if (minix_fs->block.read ((minix_fs->inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size,
                              MINIX_BLOCK_SIZE / minix_fs->block_size, minix_buffer) == 0)
    {
        minix_inode_t *inode = (minix_inode_t *) &minix_buffer;
        minix2_inode_t *inode2 = (minix2_inode_t *) &minix_buffer;

        if (minix_fs->version == 1)
        {
            if ((inode->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                debug_print ("Root inode is not a directory.\n");
                return NULL;
            }
        }
        else if (minix_fs->version == 2)
        {
            int directory_size = inode2->size;

            if ((inode2->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                debug_print ("v2: Root inode is not a directory.\n");
                return NULL;
            }

            /* Okay, so the root node is a directory. Fine and
               dandy. Let's play some games. */
            if (minix_fs->block.read ((inode2->zone[0] * MINIX_BLOCK_SIZE) /
                                      minix_fs->block_size, MINIX_BLOCK_SIZE /
                                      minix_fs->block_size, minix_buffer) == 0)
            {
                int location = 0;
                while (location < directory_size)
                {
                    minix_directory_entry_t *directory_entry = (minix_directory_entry_t *) &minix_buffer[location];
                    if (string_compare_max(filename, directory_entry->name, minix_fs->name_length) == 0)
                    {
                        return minix2_find_inode (minix_fs, directory_entry->inode);
                    }

                    location += sizeof (minix_directory_entry_t) + minix_fs->name_length;
                }
                
            }
            else
            {
                debug_print ("Reading root directory failed.\n");
            }
        }
    }   
    else
    {
        debug_print ("Reading root inode failed.\n");
    }

    return NULL;
}

/* Mount a volume. */
static return_t minix_mount (block_service_t *block)
{
    // FIXME: Use a linked list.
    minix_fs_t *minix_fs = &fs;
    block_info_t info;

    memory_copy (&minix_fs->block, block, sizeof (block_service_t));
    minix_fs->block.info (&info);
    minix_fs->block_size = info.block_size;

    if (!minix_init (minix_fs))
    {
        log.print (LOG_URGENCY_ERROR, "Not a valid Minix file system.");
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    return STORM_RETURN_SUCCESS;
}

/* Open a file. */
static return_t minix_open (char *filename, vfs_file_mode_t mode,
                            vfs_file_handle_t *handle __attribute__ ((unused)))
{
    // FIXME: Use a linked list of mounted filesystems.
    minix_fs_t *minix_fs = &fs;

    /* Check if the file exists. */
    minix2_inode_t *inode2;    

    if (minix_fs->version == 2)
    {
        inode2 = minix2_find_file (minix_fs, filename);
    }
    else
    {
        // FIXME: Implement.
        return STORM_RETURN_NOT_IMPLEMENTED;
    }

    if (mode == VFS_FILE_MODE_READ)
    {
        // FIXME: Check for read permissions.
    }
    else
    {
        // FIXME: Implement.
        return STORM_RETURN_NOT_IMPLEMENTED;
    }

    *handle = minix_get_free_handle ();
    file[*handle].inode = inode2;
    file[*handle].position = 0;

    return STORM_RETURN_SUCCESS;
}

/* Close a previously opened file. */
static return_t minix_close (vfs_file_handle_t handle)
{
    file[handle].inode = NULL;
    return STORM_RETURN_SUCCESS;
}

/* Read from a previously opened file. */
static return_t minix_read (vfs_file_handle_t handle, void *buffer,
                            size_t count)
{
    // FIXME: Use a linked list.
    minix_fs_t *minix_fs = &fs;
    minix2_inode_t *inode = file[handle].inode;
    unsigned int block = file[handle].position / MINIX_BLOCK_SIZE;

    /* Where are we in the buffer. */
    unsigned int where = 0; 

    // FIXME: We need a for loop here, with special precautions for
    // the first and last block that we are reading
    // (file[handle].position % MINIX_BLOCK_SIZE for the first and
    // count % MINIX_BLOCK_SIZE for the last). For now, just take one
    // block.

    debug_print ("block: %u\n", block);
    if (block < 7)
    {
        block = inode->zone[block];
        if (minix_fs->block.read ((block * MINIX_BLOCK_SIZE) /
                                  minix_fs->block_size, MINIX_BLOCK_SIZE /
                                  minix_fs->block_size, read_buffer) != 0)
        {
            // FIXME: Use another return value.
            return STORM_RETURN_NOT_FOUND;
        }

        memory_copy ((uint8_t *) buffer + where, read_buffer + (file[handle].position % MINIX_BLOCK_SIZE), count % MINIX_BLOCK_SIZE);
    }
    else
    {
        // FIXME: Parse the indirect and double indirect blocks.
        debug_print ("Unimplemented read! %s, %u\n", __FILE__, __LINE__);
        return STORM_RETURN_SUCCESS;
    }

    file[handle].position += count;
    return STORM_RETURN_SUCCESS;
}

/* Get information about a file. */
static return_t minix_info (char *filename UNUSED, vfs_file_info_t *info)
{
    // FIXME: Use a linked list of mounted filesystems.
    minix_fs_t *minix_fs = &fs;

    /* Check if the file exists. */
    minix2_inode_t *inode2;    

    if (minix_fs->version == 2)
    {
        inode2 = minix2_find_file (minix_fs, filename);
    }
    else
    {
        // FIXME: Implement.
        return STORM_RETURN_NOT_IMPLEMENTED;
    }

    // FIXME: Take the other fields as well. atime, mtime, ctime,
    // mode, uid, gid etc...
    info->size = inode2->size;
    return STORM_RETURN_SUCCESS;
}

/* Return some information about the filesystem service (function pointers to
   our functionality). */
static return_t service_info (void *filesystem_void)
{
    filesystem_service_t *filesystem = (filesystem_service_t *) filesystem_void;
    filesystem->magic_cookie = FILESYSTEM_COOKIE;
    filesystem->mount = &minix_mount;
    filesystem->open = &minix_open;
    filesystem->close = &minix_close;
    filesystem->read = &minix_read;
    // filesystem->write = &minix_write;
    filesystem->info = &minix_info;
    return STORM_RETURN_SUCCESS;
}

int module_start (void)
{
    //    minix2_inode_t *inode2;

    /* Contact the log service provider. */
    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }


    //    inode2 = minix2_find_file (minix_fs, "razor_1911_cracks.mod");
    //    debug_print ("%s %x %u %u\n", "razor_1911_cracks.mod",
    //                 inode2->mode, inode2->uid, inode2->gid);

    return service_register ("filesystem", "chaos development", "Minix module",
                             "1", FILESYSTEM_SERVICE_VERSION, &service_info);
}
