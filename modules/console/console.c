/* $chaos: console.c,v 1.3 2002/05/23 11:23:56 per Exp $ */
/* Abstract: Console module. Will eventually be 100% ANSI escape
             sequence compatible. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "console.h"
#include "console_output.h"

volatile unsigned int number_of_consoles = 0;
character_t *screen = (character_t *) NULL;
volatile console_t *current_console = NULL;
console_t *console_list = NULL;
//ipc_structure_type video_structure;
volatile bool has_video = FALSE;
volatile unsigned int console_id = 0;
volatile console_t *console_shortcut[12] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/* Link in this console into our linked list of consoles. */
void console_link (console_t *console)
{
    if (console_list == NULL)
    {
        console_list = console;
        console_list->next = NULL;
    }
    else
    {
        console->next = (struct console_t *) console_list;
        console_list = console;
    }
    
    console_shortcut[number_of_consoles] = console;
}

/* Function:    console_flip ()
   Purpose:     Save the console state to current_console->buffer and
                copy the contents of console->buffer to the screen.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console to flip to.
   TODO:        Support switching of video mode. */
void console_flip (console_t *console)
{
    //    video_cursor_type video_cursor;
    //    message_parameter_type message_parameter;
    //    video_mode_type video_mode;
    
    console->output = screen;
    current_console->output = current_console->buffer;

    if (current_console->type == CONSOLE_TYPE_TEXT)
    {
        memory_copy (current_console->buffer, screen,
                     current_console->width * current_console->height *
                     sizeof (character_t));
    }

    if (has_video)
    {
        /* Set the correct videomode for this console. */
        if (console->width != current_console->width ||
            console->height != current_console->height ||
            console->depth != current_console->depth ||
            console->type != current_console->type)
        {
#if FALSE
            video_mode.width = console->width;
            video_mode.height = console->height;
            video_mode.depth = console->depth;
            video_mode.mode_type = console->type;
            
            if (video_mode_set (&video_structure, &video_mode) !=
                VIDEO_RETURN_SUCCESS)
            {
                /* FIXME: Fail and return here. */
            }
#endif
        }
        
        /* Move the cursor. */
        /* FIXME: library_video should have a function for this. */
#if FALSE
        video_cursor.x = console->cursor_x;
        video_cursor.y = console->cursor_y;
        message_parameter.data = &video_cursor;
        message_parameter.block = FALSE;
        message_parameter.length = sizeof (video_cursor_type);
        message_parameter.protocol = IPC_PROTOCOL_VIDEO;
        message_parameter.message_class = IPC_VIDEO_CURSOR_PLACE;
        
        ipc_send (video_structure.output_mailbox_id, &message_parameter);
#endif
    }
    
    if (console->type == CONSOLE_TYPE_TEXT)
    {
        memory_copy (console->output, console->buffer,
                     console->width * console->height *
                     sizeof (character_t));
    }
    
    current_console = console;
} 

/* Return some information about the console service (function pointers to
   our functionality). */
static return_t service_info (void)
{
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    return service_register ("console", 1, (function_t) &service_info);
}
