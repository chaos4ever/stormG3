/* $chaos: vga.c,v 1.3 2002/05/23 11:24:03 per Exp $ */
/* Abstract: VGA server for chaos. */
/* Authors: Per Lundberg <per@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "config.h"
#include "font_8x8.h"
#include "vga.h"

/* Define this to get some debug information. */

#undef DEBUG

extern void vga_set_mode (u32 mode);

typedef struct
{
    unsigned int mode;
    unsigned int width;
    unsigned int height;
    unsigned int bpp;
    unsigned int type;
} vga_mode_type;

typedef struct
{
    u8 red, green, blue;
} __attribute__ ((packed)) vga_palette_entry_type;

vga_mode_type mode[] =
{
    { 0, 320, 200, 8, VIDEO_MODE_TYPE_GRAPHIC },
    { 1, 80,  50,  4, VIDEO_MODE_TYPE_TEXT }
};

vga_mode_type *current_mode = NULL;

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

u8 *graphic_video_memory = (u8 *) NULL;
  
#define VIDEO_MODES (sizeof (mode) / sizeof (vga_mode_type))

static tag_type empty_tag =
{
    0, 0, ""
};

/* Set up the given video mode. */

static bool mode_set (unsigned int width, unsigned int height,
                      unsigned int bpp, unsigned int type)
{
    unsigned int search;
  
    for (search = 0; search < VIDEO_MODES; search++)
    {
        if (width == mode[search].width &&
            height == mode[search].height &&
            bpp == mode[search].bpp &&
            type == mode[search].type)
        {
            vga_set_mode (mode[search].mode);
            current_mode = &mode[search];
            return TRUE;
        }
    }

    return FALSE;
}

/* Set the VGA palette. */

static void vga_palette_set (vga_palette_entry_type *palette)
{
    system_port_out_u8 (VGA_PALETTE_WRITE, 0);
    system_port_out_u8_string (VGA_PALETTE_DATA, (u8 *) palette, 256 * 3);
}

/* Set one entry in the VGA palette. */

static void vga_palette_set_entry (u8 num, vga_palette_entry_type *entry)
{
    system_port_out_u8 (VGA_PALETTE_WRITE, num);
    system_port_out_u8 (VGA_PALETTE_DATA, entry->red);
    system_port_out_u8 (VGA_PALETTE_DATA, entry->green);
    system_port_out_u8 (VGA_PALETTE_DATA, entry->blue);
}

/* Set a font. */

static void vga_font_set (u8 *font_data, unsigned int length)
{
    /* First, the sequencer. */
    /* Synchronous reset. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x00);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x01);

    /* CPU writes only to map 2. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x02);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x04);

    /* Sequential addressing. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x04);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x07);

    /* Clear synchronous reset. */
  
    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x00);

    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x03);
  
    /* Now, the graphics controller. */
    /* Select map 2. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x04);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x02);

    /* Disable odd-even addressing. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x05);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x00);

    /* Map start at A0000. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x06);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x00);
	
    memory_copy (graphic_video_memory, font_data, length);

    /* First, the sequencer. */
    /* Synchronous reset. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x00);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x01);

    /* CPU writes to maps 0 and 1. */

    system_port_out_u8_pause ( VGA_SEQUENCER_REGISTER, 0x02);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x03);

    /* Odd-even addressing. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x04);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x03);

    /* Character Map Select. */
  
    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x03);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0);

    /* Clear synchronous reset. */

    system_port_out_u8_pause (VGA_SEQUENCER_REGISTER, 0x00);
    system_port_out_u8_pause (VGA_SEQUENCER_DATA, 0x03);
  
    /* Now, the graphics controller. */
    /* Select map 0 for CPU. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x04);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x00);

    /* Enable even-odd addressing. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x05);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x10);

    /* Map starts at B8000. */

    system_port_out_u8_pause (VGA_GRAPHIC_REGISTER, 0x06);
    system_port_out_u8_pause (VGA_GRAPHIC_DATA, 0x0E);
}

/* Place the text mode cursor. When in graphics mode, this function
   does nothing. */

static void vga_cursor_place (int x, int y)
{
    int position;

    if (current_mode != NULL)
    {
        if (current_mode->type != VIDEO_MODE_TYPE_TEXT)
        {
            return;
        }
    
        position = y * current_mode->width + x;
    
        /* Cursor position high. */
    
        system_port_out_u8 (0x3D4, 0x0E);
        system_port_out_u8 (0x3D5, position / 256);
    
        /* Cursor position low. */
    
        system_port_out_u8 (0x3D4, 0x0F);
        system_port_out_u8 (0x3D5, position % 256);
    }
}
  
/* Handle the connection to the console service. */

static void handle_connection (ipc_structure_type *ipc_structure)
{
    message_parameter_type message_parameter;
    bool done = FALSE;
    u32 *data;
    unsigned int data_size = 8192;

    memory_allocate ((void *) &data, data_size);

    /* Accept the connection. */ 

    message_parameter.data = data;
    message_parameter.block = TRUE;
    message_parameter.protocol = IPC_PROTOCOL_VIDEO;

    while (!done)
    {
        message_parameter.message_class = IPC_CLASS_NONE;
        message_parameter.length = data_size;
    
        if (ipc_receive (ipc_structure->input_mailbox_id, &message_parameter,
                         &data_size) != STORM_RETURN_SUCCESS)
        {
            continue;
        }

        switch (message_parameter.message_class)
        {
            /* Place the text mode cursor. */

            case IPC_VIDEO_CURSOR_PLACE:
            {
                video_cursor_type *cursor =
                    (video_cursor_type *) message_parameter.data;

                vga_cursor_place (cursor->x, cursor->y);
                break;
            }

            /* Set the font. */

            case IPC_VIDEO_FONT_SET:
            {
                /* FIXME: Do security checks here. */

                vga_font_set ((u8 *) data, message_parameter.length);
                break;
            }

            /* Set a video mode. */

            case IPC_VIDEO_MODE_SET:
            {
                video_mode_type *video_mode =
                    (video_mode_type *) message_parameter.data;
                return_type *return_value = (return_type *) message_parameter.data;

                if (video_mode != NULL)
                {
                    message_parameter.length = sizeof (return_type);
          
                    if (mode_set (video_mode->width, video_mode->height,
                                  video_mode->depth, video_mode->mode_type))
                    {
                        if (video_mode->mode_type == VIDEO_MODE_TYPE_TEXT)
                        {
                            int index;
              
                            for (index = 0; index < 16; index++)
                            {
                                vga_palette_set_entry (index, &text_palette[index]);
                            }  
                        }
                        else if (video_mode->mode_type == VIDEO_MODE_TYPE_GRAPHIC &&
                                 video_mode->depth == 8)
                        {
                            int index;
              
                            for (index = 0; index < 256; index++)
                            {
                                vga_palette_entry_type entry;
                
                                entry.red = ((index & 0xE0) >> 5) << 3;
                                entry.green = ((index & 0x1C) >> 2) << 3;
                                entry.blue = ((index & 0x03) >> 0) << 4;
                
                                vga_palette_set_entry (index, &entry);
                            }  
              
                        }

                        *return_value = IPC_VIDEO_RETURN_SUCCESS;
                    }
                    else
                    {
                        *return_value = IPC_VIDEO_RETURN_MODE_UNAVAILABLE;
                    }
                }
                else
                {
                    *return_value = IPC_VIDEO_RETURN_MODE_UNAVAILABLE;
                }

                ipc_send (ipc_structure->output_mailbox_id, &message_parameter);

                break;
            }

            /* Set the palette. */

            case IPC_VIDEO_PALETTE_SET:
            {
                vga_palette_set ((vga_palette_entry_type *) data);

                break;
            }
        }
    }
}

/* Main function. */
return_type main (void)
{
    console_structure_type console_structure;
    
    /* Set our name. */
    system_process_name_set ("vga");
    system_thread_name_set ("Initialising");

    /* Initialise the memory library. */
    memory_init ();

    //  log_init (&log_structure, PACKAGE_NAME);

    /* Register our hardware ports. */

    if (system_call_port_range_register (VGA_PORT_BASE, VGA_PORTS, 
                                         "VGA adapter"))
    {
        //    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
        //         "Couldn't register portrange 0x3C0 - 0x3DF.");
        return -1;
    };

    /* FIXME: Actually check if an adapter is present. How is this done? */

    // if (!vga_detect ())
    // {
    //   return -1;
    // }
  
    system_call_memory_reserve (VGA_MEMORY, VGA_MEMORY_SIZE,
                                (void **) &graphic_video_memory);

    /* Create a connection to the console service. */

    if (console_init (&console_structure, &empty_tag,
                      IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_VIDEO) !=
        CONSOLE_RETURN_SUCCESS)
    {
        return -1;
    }

    system_call_process_parent_unblock ();
    system_thread_name_set ("Handling connection");
    handle_connection (&console_structure.ipc_structure);

    return 0;
}
