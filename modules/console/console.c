/* $chaos: console.c,v 1.4 2002/06/24 21:40:30 per Exp $ */
/* Abstract: Console module. Will eventually be 100% ANSI escape
             sequence compatible. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <console/console.h>

#include "console.h"
#include "console_output.h"

volatile unsigned int number_of_consoles = 0;
character_t *screen = (character_t *) NULL;
volatile console_t *current_console = NULL;
console_t *console_list = NULL;
volatile bool has_video = FALSE;
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

/* Handle keyboard events. */
static return_t console_handle_key_event (keyboard_packet_t *keyboard_packet)
{
    /* Console switching? For now, ALT + TAB is used. This should be
       customisable. */
    if (current_console != NULL)
    {
        if (keyboard_packet->key_pressed &&
            keyboard_packet->has_special_key &&
            keyboard_packet->special_key == KEYBOARD_SPECIAL_KEY_TAB &&
            (keyboard_packet->left_alt_down ||
             keyboard_packet->right_alt_down))
        {
            /* Next console. */
            console_t *new_console = (console_t *) current_console->next;
            if (new_console == NULL)
            {
                new_console = console_list;
            }
            
            if (new_console != current_console)
            {
                /* FIXME: This is not purely correct, but what the
                   heck... finish library_semaphore sometime, will
                   you? */
                while (new_console->lock == TRUE)
                {
                    //                    system_call_dispatch_next ();
                }
                
                new_console->lock = TRUE;
                console_flip (new_console);
                new_console->lock = FALSE;
            }
        }
        
        /* Bind a console to a function key. */
        if (keyboard_packet->key_pressed &&
            keyboard_packet->has_special_key &&
            keyboard_packet->special_key >= KEYBOARD_SPECIAL_KEY_F1 &&
            keyboard_packet->special_key <= KEYBOARD_SPECIAL_KEY_F10 &&
            (keyboard_packet->left_alt_down ||
             keyboard_packet->right_alt_down) &&
            (keyboard_packet->left_control_down ||
             keyboard_packet->right_control_down))
        {
            console_shortcut[keyboard_packet->special_key -
                             KEYBOARD_SPECIAL_KEY_F1] = current_console;
        }
              
        /* Switch to a previously bound console. */
        if (keyboard_packet->key_pressed &&
            keyboard_packet->has_special_key &&
            keyboard_packet->special_key >= KEYBOARD_SPECIAL_KEY_F1 &&
            keyboard_packet->special_key <= KEYBOARD_SPECIAL_KEY_F10 &&
            (keyboard_packet->left_alt_down ||
             keyboard_packet->right_alt_down))
        {
            /* New console. */
            console_t *new_console = (console_t *) console_shortcut[keyboard_packet->special_key - KEYBOARD_SPECIAL_KEY_F1];
            if (new_console != NULL)
            {
                /* FIXME: This is not purely correct, but what the
                   heck... finish library_semaphore sometime, will you? */
                while (new_console->lock == TRUE)
                {
                    //                    system_call_dispatch_next ();
                }
                
                new_console->lock = TRUE;
                console_flip (new_console);
                new_console->lock = FALSE;
            }
        }
        
        /* Send on... If we are allowed to. */
        if (current_console->active_application != NULL)
        {
            if (current_console->active_application->wants_keyboard)
            {
                // FIXME: Put it in her stdin.
            }
        }
        else if (current_console->active_application == NULL)
        {
            debug_print ("No active application.");
            // system_call_debug_print_simple ("console: Something is broken. A mutex will fix this!\n");
        }
    }        

    debug_print ("%s: We got an event. ", __FILE__);
    
    return STORM_RETURN_SUCCESS;
}

/* Open a new console. */
static return_t console_open (console_id_t *console_id, size_t width,
                              size_t height, size_t depth, int mode_type)
{
    width = height = depth = mode_type;
    *console_id = 1;
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Close a previously opened console. */
static return_t console_close (console_id_t console_id)
{
    console_id = 0;
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Return some information about the console service (function pointers to
   our functionality). */
static return_t service_info (void *console_void)
{
    console_service_t *console = (console_service_t *) console_void;
    console->magic_cookie = CONSOLE_COOKIE;
    console->key_event = &console_handle_key_event;
    console->open = &console_open;
    console->close = &console_close;
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    return service_register ("console", "chaos development", "Console module",
                             "1", 1, &service_info);
}
