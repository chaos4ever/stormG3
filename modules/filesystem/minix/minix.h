/* $chaos: minix.h,v 1.2 2002/07/10 21:23:33 per Exp $ */
/* Abstract: Minix file system data types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __MINIX_H__
#define __MINIX_H__

#include <storm/storm.h>

/* The size of a Minix block. */
#define MINIX_BLOCK_SIZE                1024

/* The amount of inodes in a block. */
#define MINIX_INODE_PER_BLOCK           (MINIX_BLOCK_SIZE / sizeof (minix_inode_t))
#define MINIX2_INODE_PER_BLOCK          (MINIX_BLOCK_SIZE / sizeof (minix2_inode_t))

/* The location of the superblock. */
#define MINIX_SUPERBLOCK_LOCATION       (MINIX_BLOCK_SIZE)

/* The root inode. */
#define MINIX_ROOT_INODE                1

/* Original Minix file system. */
#define MINIX_MAGIC                     0x137F

/* Minix file system, 30 char names. */
#define MINIX_MAGIC_EXTENDED            0x138F

/* Minix V2 file system. */
#define MINIX2_MAGIC                    0x2468

/* Minix V2 file system, 30 character names. */
#define MINIX2_MAGIC_EXTENDED           0x2478

/* The file name lengths. */
#define MINIX_FILE_NAME_LENGTH          14
#define MINIX_EXTENDED_FILE_NAME_LENGTH 30

/* Special file modes. */
#define MINIX_MODE_DIRECTORY            0040000
#define MINIX_MODE_LINK                 0120000
#define MINIX_MODE_FILE                 0100000

/* Super-block. */
typedef struct
{
    /* The number of inodes on this file system. */
    uint16_t inodes_count;

    /* The number of zones on this file system. */
    uint16_t zones_count;

    /* ??? */
    uint16_t imap_blocks;

    /* ??? */
    uint16_t zmap_blocks;

    /* ??? */
    uint16_t first_datazone;

    /* ??? */
    uint16_t log_zone_size;

    /* ??? */
    uint32_t max_size;

    /* Magic number. */
    uint16_t magic;

    /* 0, 1 = clean, 2 = errors. */
    uint16_t state;

    /* ??? */
    uint32_t zones;
} minix_superblock_t;

/* A Minix inode. */
typedef struct
{
    uint16_t mode;
    uint16_t uid;
    uint32_t size;
    uint32_t time;
    uint8_t gid;
    uint8_t nlinks;
    uint16_t zone[9];
} minix_inode_t;

/* A Minix V2 inode. */
typedef struct
{
    uint16_t mode;
    uint16_t nlinks;
    uint16_t uid;
    uint16_t gid;
    uint32_t size;
    uint32_t atime;
    uint32_t mtime;
    uint32_t ctime;
    uint32_t zone[10];
} minix2_inode_t;

/* A directory entry. The real size is dependent on the file name
   length. */
typedef struct 
{
    /* The inode of the file. */
    uint16_t inode;
    char name[0];
} minix_directory_entry_t;

/* A structure we use to keep track of a Minix file system. */
typedef struct
{
    /* The block service provider we are using. */
    block_service_t block;

    /* The size of blocks on the volume this filesystem is on. */
    size_t block_size;
    
    /* The file name length (14 or 30 characters). */
    size_t name_length;

    /* The version of the file system (1 or 2). */
    int version;

    /* The inode block number (where the inodes start). */
    unsigned int inode_block;
} minix_fs_t;

#endif /* !__MINIX_H__ */
