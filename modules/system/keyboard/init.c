/* $chaos: init.c,v 1.1 2002/08/11 21:13:31 per Exp $ */
/* Abstract: Keyboard initialization code. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "controller.h"
#include "init.h"
#include "keyboard.h"
#include "mouse.h"

#include <console/console.h>
#include <log/log.h>
#include <storm/storm.h>

/* The log service provider that we are using. */
log_service_t log;

/* The console service provider that we are using. */
console_service_t console;

/* Initialise the server. */
bool init (void)
{
    const char *message;

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

/* This function is called when the module is started. */
return_t module_start (void)
{
    volatile return_t return_value;

    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return -1; // FIXME
    }

    /* Detect whether a keyboard and/or mouse is present, and if so, put
       them into a usable state. */
    if (!init ())
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "Failed initialization.");
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
        return -1; // FIXME
    }
        
    if (has_mouse)
    {
        if (irq_register (MOUSE_IRQ, "Mouse", &mouse_irq_handler) != STORM_RETURN_SUCCESS)
        {
            log.print (LOG_URGENCY_EMERGENCY, "Failed to register mouse IRQ.");
            return -1;
        }
    }

    /* Everything else worked out alright. Register us with the
       console server. */
    return_value = console_lookup (&console);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    key_event = console.key_event;
    if (has_mouse)
    {
        //        mouse_handler = console->handle_mouse_event;
    }
    
    return STORM_RETURN_SUCCESS;
}
