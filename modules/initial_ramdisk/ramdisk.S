/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: The ramdisk. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#define ASSEMBLER			1
#include "ramdisk.h"
	
ramdisk:
/* Because of the fact that we don't chdir... */
.incbin					"initial_ramdisk/ramdisk.image"
blocks:	 		.int		(. - ramdisk) / RAMDISK_BLOCK_SIZE
