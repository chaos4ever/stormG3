/* $chaos: minix.c,v 1.1 2002/07/09 08:37:37 per Exp $ */
/* Abstract: Implementation of the Minix file system. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <log/log.h>

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
static minix2_inode_t *find_inode2 (minix_fs_t *minix_fs, unsigned int number)
{
    unsigned int inode_block = minix_fs->inode_block + (number - 1) / MINIX2_INODE_PER_BLOCK;
    unsigned int inode_which = (number - 1) % MINIX2_INODE_PER_BLOCK;

    minix_fs->block.read ((inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, &minix_buffer2);
    return (minix2_inode_t *) (&minix_buffer2[inode_which * sizeof (minix2_inode_t)]);
}

int module_start (void)
{
    minix_fs_t *minix_fs = &fs;
    block_info_t info;

    /* Contact the log service provider. */
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    if (block_resolve (&minix_fs->block) != BLOCK_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "No block device found.");
        return -1;
    }

    minix_fs->block.info(&info);
    minix_fs->block_size = info.block_size;

    /* Make sure this is a valid Minix file system. */
    if (minix_fs->block.read (MINIX_SUPERBLOCK_LOCATION / minix_fs->block_size, 
                              MINIX_BLOCK_SIZE / minix_fs->block_size,
                              superblock) == 0)
    {
        if (superblock->magic == MINIX_MAGIC)
        {
            minix_fs->version = 1;
            minix_fs->name_length = 14;
        }
        else if (superblock->magic == MINIX_MAGIC_EXTENDED)
        {
            minix_fs->version = 1;
            minix_fs->name_length = 30;
        }
        else if (superblock->magic == MINIX2_MAGIC)
        {
            minix_fs->version = 2;
            minix_fs->name_length = 14;
        }
        else if (superblock->magic == MINIX2_MAGIC_EXTENDED)
        {
            minix_fs->version = 2;
            minix_fs->name_length = 30;
        }
        else
        {
            debug_print ("Not a valid file system.\n");
            return -1;
        }

        debug_print ("Minix file system version %d found.\n", minix_fs->version);

        if (superblock->state == 1)
        {
            debug_print ("Filesystem is clean.\n");
        }
        else
        {
            debug_print ("File system has errors.\n");
            return -1;
        }
    }
    else
    {
        debug_print ("Reading from block service failed.\n");
    }

    minix_fs->inode_block = (2 + superblock->imap_blocks +
                             superblock->zmap_blocks);

    /* Okay, it is a file system. Now, read the first inode. */
    if (minix_fs->block.read ((minix_fs->inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, minix_buffer) == 0)
    {
        minix_inode_t *inode = (minix_inode_t *) &minix_buffer;
        minix2_inode_t *inode2 = (minix2_inode_t *) &minix_buffer;

        if (minix_fs->version == 1)
        {
            if ((inode->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                debug_print ("Root inode is not a directory.\n");
                return -1;
            }
        }
        else if (minix_fs->version == 2)
        {
            int directory_size = inode2->size;

            if ((inode2->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                debug_print ("v2: Root inode is not a directory.\n");
                return -1;
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
                    inode2 = find_inode2 (minix_fs, directory_entry->inode);
                    debug_print ("%s %x %u %u\n", directory_entry->name,
                                 inode2->mode, inode2->uid, inode2->gid);
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
    
    return 0;
}
