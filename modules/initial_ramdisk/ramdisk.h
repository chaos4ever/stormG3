/* $chaos: ramdisk.h,v 1.2 2002/06/26 06:45:43 per Exp $ */
/* Abstract: Ramdisk header file. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __RAMDISK_H__
#define __RAMDISK_H__

/* This file gets included from ramdisk.S so we need to take some
   special precautions. */
#ifndef ASSEMBLER

extern const uint8_t ramdisk[];

/* The number of blocks in this ramdisk. */
extern unsigned int ramdisk_block_count;

#endif

/* The block size of the ramdisk. */
#define RAMDISK_BLOCK_SIZE              512

/* The version of the block protocol we are implement. FIXME: move to
   the block library. */
#define BLOCK_VERSION                   1

#endif /* !__RAMDISK_H__ */
