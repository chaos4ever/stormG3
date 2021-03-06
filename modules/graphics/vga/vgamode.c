/* $chaos: vgamode.c,v 1.1 2002/08/13 19:14:23 per Exp $ */
/* Abstract: Mode setting code. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* Much of this code was taken from vgadrv.c in svgalib -- thanks to
   you guys! */

/* BIOS mode 03h - 80x25 text */
static const char t80x25_regs[60] =
{
    0x5B, 0x4F, 0x53, 0x37, 0x51, 0x5B, 0x6C, 0x1F, 0x00, 0x0D, 0x0a, 0x0c,
    0x00, 0x00, 0x00, 0x00, 0x5E, 0x2B, 0x5D, 0x28, 0x0F, 0x5E, 0x0A, 0xA3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07, 0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0x3E, 0x3F, 0x0A, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00, 0xFF,
    0x03, 0x01, 0x03, 0x00, 0x03,
    0xA7
};

/* BIOS mode 0Dh - 320x200x16 */
static const unsigned char g320x200x16_regs[60] =
{
    0x2D, 0x27, 0x28, 0x90, 0x2B, 0x80, 0xBF, 0x1F, 0x00, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x14, 0x00, 0x96, 0xB9, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x09, 0x0F, 0x00, 0x06,
    0x63
};

/* BIOS mode 0Eh - 640x200x16 */
static const unsigned char g640x200x16_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0x63
};

/* BIOS mode 10h - 640x350x16 */
static const unsigned char g640x350x16_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x85, 0x5D, 0x28, 0x0F, 0x63, 0xBA, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xA3
};

/* BIOS mode 12h - 640x480x16 */
static const unsigned char g640x480x16_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xEA, 0x8C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE3
};

/* BIOS mode 13h - 320x200x256 */
static const unsigned char g320x200x256_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x0E,
    0x63
};

/* non-BIOS mode - 320x240x256 */
static const unsigned char g320x240x256_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0D, 0x3E, 0x00, 0x41, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xEA, 0xAC, 0xDF, 0x28, 0x00, 0xE7, 0x06, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE3
};

/* non-BIOS mode - 320x400x256 */
static const unsigned char g320x400x256_regs[60] =
{
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0x63
};

/* non-BIOS mode - 360x480x256 */
static const unsigned char g360x480x256_regs[60] =
{
    0x6B, 0x59, 0x5A, 0x8E, 0x5E, 0x8A, 0x0D, 0x3E, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xEA, 0xAC, 0xDF, 0x2D, 0x00, 0xE7, 0x06, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE7
};

/* monochrome mode based on BIOS mode 12h - 640x480x2 */
#define g640x480x2_regs g640x480x16_regs

/* non BIOS mode - 720x348x2 based on mode 10h */
static const unsigned char g720x348x2_regs[60] =
{
    0x6B, 0x59, 0x5A, 0x8E, 0x5E, 0x8A, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x85, 0x5D, 0x2D, 0x0F, 0x63, 0xBA, 0xE3,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xA7
};

#if FALSE
static int setregs(const unsigned char *regs)
{
    int i;

    if(__svgalib_novga) return 1;

    if (__svgalib_chipset == EGA) {
	/* Enable graphics register modification */
	port_out(0x00, GRA_E0);
	port_out(0x01, GRA_E1);
    }
    /* update misc output register */
    __svgalib_outmisc(regs[MIS]);

    /* synchronous reset on */
    __svgalib_outseq(0x00,0x01);

    /* write sequencer registers */
    __svgalib_outseq(0x01,regs[SEQ + 1] | 0x20);
    port_out(1, SEQ_I);
    port_out(regs[SEQ + 1] | 0x20, SEQ_D);
    for (i = 2; i < SEQ_C; i++) {
       __svgalib_outseq(i,regs[SEQ + i]);
    }

    /* synchronous reset off */
    __svgalib_outseq(0x00,0x03);

    if (__svgalib_chipset != EGA) {
	/* deprotect CRT registers 0-7 */
        __svgalib_outcrtc(0x11,__svgalib_incrtc(0x11)&0x7f);
    }
    /* write CRT registers */
    for (i = 0; i < CRT_C; i++) {
        __svgalib_outcrtc(i,regs[CRT + i]);
    }

    /* write graphics controller registers */
    for (i = 0; i < GRA_C; i++) {
	port_out(i, GRA_I);
	port_out(regs[GRA + i], GRA_D);
    }

    /* write attribute controller registers */
    for (i = 0; i < ATT_C; i++) {
	port_in(__svgalib_IS1_R);		/* reset flip-flop */
	__svgalib_delay();
	port_out(i, ATT_IW);
	__svgalib_delay();
	port_out(regs[ATT + i], ATT_IW);
	__svgalib_delay();
    }

    return 0;
}
#endif
