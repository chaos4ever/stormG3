/* $chaos: halt.c,v 1.1 2002/08/11 18:39:02 per Exp $ */
/* Abstract: Functions for halting the machine. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/halt.h>
#include <storm/ia32/types.h>

/* Halt the computer. */
return_t halt (enum halt_t type)
{
    uint16_t idtr[3] = 
    {
        0x0000, 
        0x0000,
        0x0000
    };

    switch (type)
    {
        case HALT_REBOOT:
        {
            asm volatile ("lidt      (%0)\n"
                          "int       $0" 
                          : 
                          :
                          "g" (idtr));
            break;
        }
        case HALT_SHUTDOWN:
        {
            debug_print ("System has been shut down. You may power off.\n");
            cpu_interrupts_disable ();
            while (TRUE)
            {
                asm ("hlt");
            }
            break;
        }

        default:
        {
            return STORM_RETURN_INVALID_ARGUMENT;
        }
    }
            
    /* We should never get here. */
    return STORM_RETURN_SUCCESS;
}
