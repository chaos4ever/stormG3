/* $chaos: ramdisk.S,v 1.1 2002/07/09 10:07:38 per Exp $ */
/* Abstract: The ramdisk. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#define ASSEMBLER			1
#include "ramdisk.h"

.data
.globl			ramdisk
.globl			ramdisk_block_count

ramdisk:
/* Because of the fact that we don't chdir... */
.incbin					"block/initial_ramdisk/ramdisk.image"

ramdisk_block_count: 	.int		(. - ramdisk) / RAMDISK_BLOCK_SIZE
