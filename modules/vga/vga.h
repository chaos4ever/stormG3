/* $chaos: vga.h,v 1.2 2002/05/23 11:24:03 per Exp $ */
/* Abstract: VGA header file. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VGA_H__
#define __VGA_H__

#define VGA_PORT_BASE           0x3C0
#define VGA_PORTS               32
#define VGA_PALETTE_READ        (VGA_PORT_BASE + 7)
#define VGA_PALETTE_WRITE       (VGA_PORT_BASE + 8)
#define VGA_PALETTE_DATA        (VGA_PORT_BASE + 9)
#define VGA_SEQUENCER_REGISTER  0x3C4
#define VGA_SEQUENCER_DATA      0x3C5
#define VGA_GRAPHIC_REGISTER    0x3CE
#define VGA_GRAPHIC_DATA        0x3CF

#define VGA_MEMORY              0xA0000
#define VGA_MEMORY_SIZE         (64 * KB)

#endif /* !__VGA_H__ */
