/* $chaos: minix.c,v 1.2 2002/07/10 21:23:33 per Exp $ */
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
    if (minix_fs->block.read ((minix_fs->inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, minix_buffer) == 0)
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

/* Return some information about the filesystem service (function pointers to
   our functionality). */
static return_t service_info (void *filesystem_void)
{
    filesystem_service_t *filesystem = (filesystem_service_t *) filesystem_void;
    filesystem->magic_cookie = FILESYSTEM_COOKIE;
    // filesystem->mount = &minix_mount;
    // filesystem->read = &minix_read;
    return STORM_RETURN_SUCCESS;
}

int module_start (void)
{
    minix_fs_t *minix_fs = &fs;
    block_info_t info;
    //    minix2_inode_t *inode2;

    /* Contact the log service provider. */
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    /* Resolve a block device. FIXME: Remove this code and replace it
       with VFS mounting. */
    if (block_resolve (&minix_fs->block) != BLOCK_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "No block device found.");
        return -1;
    }

    minix_fs->block.info(&info);
    minix_fs->block_size = info.block_size;

    if (!minix_init (minix_fs))
    {
        log.print (LOG_URGENCY_EMERGENCY, "Not a valid Minix file system.");
        return -1;
    }

    //    inode2 = minix2_find_file (minix_fs, "razor_1911_cracks.mod");
    //    debug_print ("%s %x %u %u\n", "razor_1911_cracks.mod",
    //                 inode2->mode, inode2->uid, inode2->gid);

    return service_register ("filesystem", "chaos development", "Minix module",
                             "1", FILESYSTEM_SERVICE_VERSION, &service_info);
}
