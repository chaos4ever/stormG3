/* $chaos: init.c,v 1.5 2002/06/20 22:42:25 per Exp $ */
/* Abstract: Keyboard initialization code. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "controller.h"
#include "init.h"
#include "keyboard.h"
#include "mouse.h"

#include <log/log.h>
#include <storm/storm.h>

/* The log service provider that we are using. */
log_service_t log;

/* Initialise the server. */
bool init (void)
{
    const char *message;
    log_init_t handler;

    /* Find the log service. */
    if (service_resolve ("log", 1, (function_t *) &handler) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolved log service provider.\n");
        return FALSE;
    }
    handler (&log);

    /* Try to allocate the keyboard controller's ports. */
    if (port_range_register (CONTROLLER_PORT_BASE,
                             CONTROLLER_PORTS,
                             "Keyboard controller") !=
        STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "Could not allocate portrange 0x60 - 0x6F.");
        return FALSE;
    }
    
    /* Flush any pending input. */
    keyboard_clear_input ();
    
    message = keyboard_init ();
    if (message != NULL)
    {
        log.print (LOG_URGENCY_ERROR, (char *) message);
    }
    
    /* Initialise a PS/2 mouse port, if found. */
    mouse_init ();

    return TRUE;
}

return_t module_start (void)
{
    /* Detect whether a keyboard and/or mouse is present, and if so, put
       them into a usable state. */
    if (!init ())
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "Failed initialisation.");
        return STORM_RETURN_NOT_FOUND; // FIXME: Use another return value.;
    }

    log.print (LOG_URGENCY_INFORMATIVE,
               "Keyboard found at I/O 0x60-0x6F, IRQ 1.");

    if (has_mouse)
    {
        log.print (LOG_URGENCY_INFORMATIVE, "Mouse found at IRQ 12.");
    }

    if (irq_register (KEYBOARD_IRQ, "Keyboard", &keyboard_irq_handler) != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Failed to register keyboard IRQ.");
        return -1;
    }
        
    if (has_mouse)
    {
        if (irq_register (MOUSE_IRQ, "Mouse", &mouse_irq_handler) != STORM_RETURN_SUCCESS)
        {
            log.print (LOG_URGENCY_EMERGENCY, "Failed to register mouse IRQ.");
            return -1;
        }
    }
    
    return 0;
}
