/* $chaos: ramdisk.S,v 1.4 2002/07/06 07:55:16 per Exp $ */
/* Abstract: The ramdisk. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#define ASSEMBLER			1
#include "ramdisk.h"

.data
.globl			ramdisk
.globl			ramdisk_block_count

ramdisk:
/* Because of the fact that we don't chdir... */
.incbin					"block/initial_ramdisk/ramdisk.image"

ramdisk_block_count: 	.int		(. - ramdisk) / RAMDISK_BLOCK_SIZE
