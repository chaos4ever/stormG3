/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Keyboard initialization code. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "controller.h"
#include "init.h"
#include "keyboard.h"
#include "mouse.h"

#include <storm/storm.h>

/* Initialise the server. */
bool init (void)
{
    //    const char *message;

    /* Try to allocate the keyboard controller's ports. */
    /*  if (system_call_port_range_register (CONTROLLER_PORT_BASE,
        CONTROLLER_PORTS,
        "Keyboard controller") !=
        STORM_RETURN_SUCCESS)
        {
        //    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
        //               "Could not allocate portrange 0x60 - 0x6F.");
        return FALSE;
        }
    */
    
    /* Flush any pending input. */
    keyboard_clear_input ();
    
    //    message = keyboard_init ();
    //    if (message != NULL)
    {
        //  debug_print ("%s\n", message);
        //log_print (&log_structure, LOG_URGENCY_ERROR, message);
    }
    
    /* Initialise a PS/2 mouse port, if found. */
    //    mouse_init ();

    return TRUE;
}

return_t module_start (void)
{
    /* Detect whether a keyboard and/or mouse is present, and if so, put
       them into a usable state. */
    if (!init ())
    {
        //    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
        //               "Failed initialisation.");
        return 0;
    }

    return 0;

    //  log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
    //             "Keyboard found at I/O 0x60-0x6F, IRQ 1.");

    if (has_mouse)
    {
        //    log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
        //               "Mouse found at IRQ 12.");
    }

    if (irq_register (KEYBOARD_IRQ, "Keyboard IRQ", &keyboard_irq_handler) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to register keyboard IRQ.\n");
        return -1;
    }
        
    if (has_mouse)
    {
        if (irq_register (MOUSE_IRQ, "Mouse IRQ", &mouse_irq_handler) != STORM_RETURN_SUCCESS)
        {
            debug_print ("Failed to register mouse IRQ.\n");
            return -1;
        }
    }
    
    return 0;
}
