/* $chaos: ramdisk.S,v 1.2 2002/06/26 06:42:13 per Exp $ */
/* Abstract: The ramdisk. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#define ASSEMBLER			1
#include "ramdisk.h"

.data
.globl			blocks
ramdisk:
/* Because of the fact that we don't chdir... */
.incbin					"initial_ramdisk/ramdisk.image"
blocks:	 		.int		(. - ramdisk) / RAMDISK_BLOCK_SIZE
