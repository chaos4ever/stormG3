/* $chaos: system_call.c,v 1.4 2002/10/28 22:26:31 per Exp $ */
/* Abstract: */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/system_call.h>

/* Set up the system call handler in the IDT. */
void system_call_init (void)
{
    idt_setup_interrupt_gate (SYSTEM_CALL_IDT_ENTRY,
                              KERNEL_CODE_SELECTOR, system_call_lowlevel, 3);
}

/* The high-level system call handler, called from the low-level function. */
return_t system_call (uint32_t *stack)
{
    switch (SYSTEM_CALL_NUMBER)
    {
        /* Get the list of service providers for a service. */
        case SYSTEM_CALL_SERVICE_LOOKUP:
        {
            // FIXME: Add capability check here?
            if (SYSTEM_CALL_ARGUMENTS == 3)
            {
                service_lookup_t *lookup = (service_lookup_t *) SYSTEM_CALL_ARGUMENT_0;
                service_lookup (lookup->name, lookup->vendor,
                                lookup->model, lookup->device_id,
                                lookup->major_version, lookup->minor_version,
                                (size_t *) SYSTEM_CALL_ARGUMENT_1,
                                (service_t **) SYSTEM_CALL_ARGUMENT_2);
                return STORM_RETURN_SUCCESS;
            }
            else
            {
                debug_print ("Invalid number of arguments in SYSTEM_CALL_SERVICE_LOOKUP");
                return STORM_RETURN_INVALID_ARGUMENT;
            }
            break;
        }

        /* Connect to a service provider. */
        case SYSTEM_CALL_SERVICE_CONNECT:
        {
            return STORM_RETURN_NOT_IMPLEMENTED;
            break;
        }

        /* Close a previously opened connection to a service
           provider. */
        case SYSTEM_CALL_SERVICE_CLOSE:
        {
            return STORM_RETURN_NOT_IMPLEMENTED;
            break;
        }

        /* Invoke a function in a service provider. */
        case SYSTEM_CALL_SERVICE_INVOKE:
        {
            return STORM_RETURN_NOT_IMPLEMENTED;
            break;
        }

        /* An unsupported system call. */
        default:
        {
            debug_print ("Invalid system call executed: %u\n", stack[0]);
            return STORM_RETURN_INVALID_ARGUMENT;
            break;
        }
    }
}
