/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Implementation of the Minix file system. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

// #include <storm/storm.h>

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "minix.h"

// FIXME: Remove when we are connecting to a block service provider.
#define BLOCK_SIZE                      512

// FIXME: Have these dynamically allocated.
uint8_t minix_superblock_buffer[MINIX_BLOCK_SIZE];
minix_superblock_t *superblock = (minix_superblock_t *) &minix_superblock_buffer;
// FIXME: One of these for each volume mounted.
minix_fs_t fs;

uint8_t minix_buffer[MINIX_BLOCK_SIZE];
uint8_t minix_buffer2[MINIX_BLOCK_SIZE];

/* Read a block from the given file (should be a block device when
   testing is done). */
static int block_read (minix_fs_t *minix_fs, size_t block_start, size_t blocks, void *buffer)
{
    if (fseek (minix_fs->file, block_start * minix_fs->block_size, SEEK_SET) != 0) 
    {
        return -1;
    }

    if (fread (buffer, minix_fs->block_size, blocks, minix_fs->file) != blocks)
    {
        return -1;
    }

    return 0;
}

/* Find an inode with the given inode number. */
static minix2_inode_t *find_inode2 (minix_fs_t *minix_fs, unsigned int number)
{
    unsigned int inode_block = minix_fs->inode_block + (number - 1) / MINIX2_INODE_PER_BLOCK;
    unsigned int inode_which = (number - 1) % MINIX2_INODE_PER_BLOCK;

    block_read (minix_fs, (inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, &minix_buffer2);
    return (minix2_inode_t *) (&minix_buffer2[inode_which * sizeof (minix2_inode_t)]);
}

int main (void)
{
    minix_fs_t *minix_fs = &fs;

    minix_fs->file = fopen ("ramdisk.image", "rb");
    if (minix_fs->file == NULL)
    {
        fprintf (stderr, "fopen failed: %s\n", strerror(errno));
        return -1;
    }

    minix_fs->block_size = BLOCK_SIZE;

    /* Make sure this is a valid Minix file system. */
    if (block_read (minix_fs, MINIX_SUPERBLOCK_LOCATION / BLOCK_SIZE, 
                    MINIX_BLOCK_SIZE / minix_fs->block_size, superblock) == 0)
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
            fprintf (stderr, "Not a valid file system.\n");
            return -1;
        }

        printf ("Minix file system version %d found.\n", minix_fs->version);

        if (superblock->state == 1)
        {
            printf ("Filesystem is clean.\n");
        }
        else
        {
            fprintf (stderr, "File system has errors.\n");
            return -1;
        }
    }
    else
    {
        fprintf (stderr, "Reading from block service failed.\n");
    }

    minix_fs->inode_block = (2 + superblock->imap_blocks +
                             superblock->zmap_blocks);

    /* Okay, it is a file system. Now, read the first inode. */
    if (block_read (minix_fs, (minix_fs->inode_block * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, minix_buffer) == 0)
    {
        minix_inode_t *inode = (minix_inode_t *) &minix_buffer;
        minix2_inode_t *inode2 = (minix2_inode_t *) &minix_buffer;

        if (minix_fs->version == 1)
        {
            if ((inode->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                fprintf (stderr, "Root inode is not a directory.\n");
                return -1;
            }
            printf ("%o %u %u\n", inode->mode, inode->uid, inode->gid);
        }
        else if (minix_fs->version == 2)
        {
            int directory_size = inode2->size;

            if ((inode2->mode & MINIX_MODE_DIRECTORY) != MINIX_MODE_DIRECTORY)
            {
                fprintf (stderr, "v2: Root inode is not a directory.\n");
                return -1;
            }

            /* Okay, so the root node is a directory. Fine and
               dandy. Let's play some games. */
            if (block_read (minix_fs, (inode2->zone[0] * MINIX_BLOCK_SIZE) / minix_fs->block_size, MINIX_BLOCK_SIZE / minix_fs->block_size, minix_buffer) == 0)
            {
                int location = 0;
                while (location < directory_size)
                {
                    minix_directory_entry_t *directory_entry = (minix_directory_entry_t *) &minix_buffer[location];
                    inode2 = find_inode2 (minix_fs, directory_entry->inode);
                    printf ("%-30s %6o %u %u\n", directory_entry->name,
                            inode2->mode, inode2->uid, inode2->gid);
                    location += sizeof (minix_directory_entry_t) + minix_fs->name_length;
                }
                
            }
            else
            {
                fprintf (stderr, "Reading root directory failed.\n");
            }
        }
    }   
    else
    {
        fprintf (stderr, "Reading root inode failed.\n");
    }
    
    fclose (minix_fs->file);

    return 0;
}
