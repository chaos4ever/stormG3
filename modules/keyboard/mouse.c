/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: PS/2 mouse code for the keyboard server. */
/* Author: Per Lundberg <per@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>

#include "controller.h"
#include "mouse.h"

/* Have we got a PS/2 mouse port? As of yet, we don't probe for the
   actual existance of a *mouse*, just the port. This makes
   hotswapping PS/2 mice easy. */
bool has_mouse = FALSE;

/* This buffer holds the mouse scan codes. The PS/2 protocol sends
   three characters for each event. */
static uint8_t mouse_buffer[3];
static int mouse_buffer_position = 0;

/* The number of mouse replies expected. */
static int mouse_replies_expected = 0;

/* Hold the state of the mouse somewhere. */
static mouse_type mouse;

/* Handler for the mouse IRQ. */
void mouse_irq_handler (unsigned int irq __attribute__ ((unused)))
{
    handle_event ();
}

/* Handle a mouse event. */
void mouse_handle_event (uint8_t scancode)
{
    if (mouse_replies_expected > 0) 
    {
        if (scancode == MOUSE_ACK) 
        {
            mouse_replies_expected--;
            return;
        }
        
        mouse_replies_expected = 0;
    }
    
    /* Add this scancode to the mouse event queue. */
    mouse_buffer[mouse_buffer_position] = scancode;
    mouse_buffer_position++;
    
    /* If the buffer is full, parse this event. */
    if (mouse_buffer_position == 3)
    {
        mouse_buffer_position = 0;
        
        mouse.button_state = mouse_buffer[0] & MOUSE_BUTTON_MASK;
        
        /* Some PS/2 mice send reports with negative bit set in
           data[0] and zero for movement.  I think this is a bug in
           the mouse, but working around it only causes artifacts when
           the actual report is -256; they'll be treated as zero. This
           should be rare if the mouse sampling rate is set to a
           reasonable value; the default of 100 Hz is plenty. (Stephen
           Tell) */
        /* Have the mouse moved horizontally? */
        if (mouse_buffer[1] == 0)
        {
            mouse.delta_x = 0;
        }
        else
        {
            mouse.delta_x = (mouse_buffer[0] & MOUSE_NEGATIVE_X) != 0 ?
                mouse_buffer[1] - 256 :
                mouse_buffer[1];
        }
        
        /* Or vertically? */
        if (mouse_buffer[2] == 0)
        {
            mouse.delta_y = 0;
        }
        else
        {
            mouse.delta_y = (mouse_buffer[0] & MOUSE_NEGATIVE_Y) != 0 ?
                mouse_buffer[2] - 256 :
                mouse_buffer[2];
        }
        
        mouse.x += mouse.delta_x;
        mouse.y -= mouse.delta_y;
        
        /* Make sure we don't get Type'o Negative. */
        if (mouse.x < 0)
        {
            mouse.x = 0;
        }
        
        if (mouse.y < 0)
        {
            mouse.y = 0;
        }
    }
}

/* Write a PS/2 mouse command. */
static void mouse_write_command (int command)
{
    controller_wait ();
    controller_write_command (CONTROLLER_COMMAND_WRITE_MODE);
    controller_wait ();
    controller_write_output (command);
}

/* Send a byte to the PS/2 mouse & handle returned ACK. */
static void mouse_write_ack (int value)
{
    controller_wait ();
    controller_write_command (CONTROLLER_COMMAND_WRITE_MOUSE);
    controller_wait ();
    controller_write_output (value);
    
    /* We expect an ACK in response. */
    mouse_replies_expected++;
    controller_wait ();
}
 
/* Check if this is a dual port controller. */
static bool detect_ps2_port(void)
{
    int loops;
    bool return_value = FALSE;
    
    /* Put the value 0x5A in the output buffer using the "Write
       Auxiliary Device Output Buffer" command (0xD3). Poll the Status
       Register for a while to see if the value really turns up in the
       Data Register. If the KEYBOARD_STATUS_MOUSE_OBF bit is also set
       to 1 in the Status Register, we assume this controller has an
       Auxiliary Port (a.k.a. Mouse Port). */
    controller_wait ();
    controller_write_command (CONTROLLER_COMMAND_WRITE_MOUSE_OUTPUT_BUFFER);
    
    controller_wait ();
    
    /* 0x5A is a random dummy value. */
    controller_write_output (0x5A);
    
    for (loops = 0; loops < 10;  loops++)
    {
        unsigned char status = controller_read_status();
        
        if ((status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) != 0)
        {
            (void) controller_read_input ();
            if ((status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) != 0)
            {
                return_value = TRUE;
            }
            break;
        }
        
        asm ("hlt");
        //system_sleep (1);
    }
    
    return return_value;
}

/* Initialise the PS/2 mouse support. */
bool mouse_init (void)
{
    if (!detect_ps2_port ())
    {
        return FALSE;
    }  
    
    has_mouse = TRUE;
  
    /* Enable the PS/2 mouse port. */
    controller_write_command_word (CONTROLLER_COMMAND_MOUSE_ENABLE);

    /* Samples/sec. */
    mouse_write_ack (MOUSE_SET_SAMPLE_RATE);
    mouse_write_ack (MOUSE_SAMPLES_PER_SECOND);

    /* 8 counts per mm. */
    mouse_write_ack (MOUSE_SET_RESOLUTION);
    mouse_write_ack (3);

    /* 2:1 scaling */
    mouse_write_ack (MOUSE_SET_SCALE21);
    
    /* Enable the PS/2 device. */
    mouse_write_ack (MOUSE_ENABLE_DEVICE);

    /* Enable controller interrupts. */
    mouse_write_command (MOUSE_INTERRUPTS_ON);
  
    return TRUE;
}
