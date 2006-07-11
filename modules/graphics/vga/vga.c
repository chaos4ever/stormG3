/* $chaos: vga.c,v 1.5 2002/11/21 21:47:55 per Exp $ */
/* Abstract: VGA server for chaos. */
/* Authors: Per Lundberg <per@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <memory/memory.h>
#include <video/video.h>

#include "font_8x8.h"
#include "vga.h"

/* Define this to get some debug information. */
#undef DEBUG

// FIXME.
vga_mode_type mode[] =
{
    /*    { 0, 320, 200, 8, VIDEO_MODE_TYPE_GRAPHIC },
          { 1, 80,  50,  4, VIDEO_MODE_TYPE_TEXT } */
    { 1, 80, 25, 4, 0 }
};

vga_mode_type *current_mode = &mode[0];

vga_palette_entry_type text_palette[] =
{ 
    /* Dark. */
    { 0x00, 0x00, 0x00 }, /* Black. */
    { 0x08, 0x08, 0x18 }, /* Blue. */
    { 0x08, 0x18, 0x08 }, /* Green. */
    { 0x08, 0x18, 0x18 }, /* Cyan. */
    { 0x18, 0x08, 0x08 }, /* Red. */
    { 0x18, 0x08, 0x18 }, /* Purple. */
    { 0x18, 0x18, 0x08 }, /* Brown. */
    { 0x28, 0x28, 0x28 }, /* Gray. */

    /* Light. */
    { 0x20, 0x20, 0x20 }, /* Dark gray. */
    { 0x28, 0x28, 0x38 },
    { 0x28, 0x38, 0x28 },
    { 0x28, 0x38, 0x38 },
    { 0x38, 0x28, 0x28 },
    { 0x38, 0x28, 0x38 },
    { 0x38, 0x38, 0x28 }, /* Yellow. */
    { 0x38, 0x38, 0x38 }  /* White. */
};

uint8_t *graphic_video_memory = (uint8_t *) NULL;
  
#define VIDEO_MODES (sizeof (mode) / sizeof (vga_mode_type))

/* Set the VGA palette. */
#if FALSE
static void vga_palette_set (vga_palette_entry_type *palette)
{
    port_uint8_out (VGA_PALETTE_WRITE, 0);
    port_uint8_out_string (VGA_PALETTE_DATA, (uint8_t *) palette, 256 * 3);
}

/* Set one entry in the VGA palette. */
static void vga_palette_set_entry (uint8_t num, vga_palette_entry_type *entry)
{
    port_uint8_out (VGA_PALETTE_WRITE, num);
    port_uint8_out (VGA_PALETTE_DATA, entry->red);
    port_uint8_out (VGA_PALETTE_DATA, entry->green);
    port_uint8_out (VGA_PALETTE_DATA, entry->blue);
}

/* Set a font. */
static void vga_font_set (uint8_t *font_data, unsigned int length)
{
    /* First, the sequencer. */
    /* Synchronous reset. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x01);

    /* CPU writes only to map 2. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x02);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x04);

    /* Sequential addressing. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x04);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x07);

    /* Clear synchronous reset. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);
  
    /* Now, the graphics controller. */
    /* Select map 2. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x04);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x02);

    /* Disable odd-even addressing. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x05);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);

    /* Map start at A0000. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x06);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);
	
    memory_copy (graphic_video_memory, font_data, length);

    /* First, the sequencer. */
    /* Synchronous reset. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x01);

    /* CPU writes to maps 0 and 1. */
    port_uint8_out_pause ( VGA_SEQUENCER_REGISTER, 0x02);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);

    /* Odd-even addressing. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x04);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);

    /* Character Map Select. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x03);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0);

    /* Clear synchronous reset. */
    port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
    port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);
  
    /* Now, the graphics controller. */
    /* Select map 0 for CPU. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x04);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);

    /* Enable even-odd addressing. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x05);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x10);

    /* Map starts at B8000. */
    port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x06);
    port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x0E);
}

#endif

/* Place the text mode cursor. When in graphics mode, this function
   does nothing. */
static return_t vga_cursor_place (int x, int y)
{
    int position;

    if (current_mode != NULL)
    {
        position = y * current_mode->width + x;
    
        /* Cursor position high. */
        port_uint8_out (0x3D4, 0x0E);
        port_uint8_out (0x3D5, position / 256);
    
        /* Cursor position low. */
        port_uint8_out (0x3D4, 0x0F);
        port_uint8_out (0x3D5, position % 256);
    }

    return STORM_RETURN_SUCCESS;
}
  
/* Return some information about the video service (function pointers
   to our functionality). */
static return_t service_info (void *video_void)
{
    video_service_t *video = (video_service_t *) video_void;
    video->cursor_place = &vga_cursor_place;
    return STORM_RETURN_SUCCESS;
}

/* Main function. */
return_t module_start (void)
{
    /* Register our hardware ports. */
    if (port_range_register (VGA_PORT_BASE, VGA_PORTS,  "VGA adapter"))
    {
        return -1;
    };

    /* FIXME: Actually check if an adapter is present. How is this done? */

    /* Create the service. */
    service_register_t service_register_info;
    service_register_info.service_vendor = "chaos development";
    service_register_info.model = "VGA";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &service_info;

    // FIXME: Fill in this structure to let user-level programs access
    // this service provider.
    service_method_t service_method[] =
        {
            { -1, NULL }
        };
    
    return video_register (&service_register_info, service_method);
}
