/* $chaos: system_call.c,v 1.8 2002/11/30 12:16:36 per Exp $ */
/* Abstract: System call implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/service.h>
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
            bool result;

            /* Does this user have the kernel::service_lookup
               capability? FIXME: I believe there is no point in this;
               it is not a security risk to be able to list service
               providers. */
            if (capability_has (PROCESS_ID_NONE, dispatch_current_process,
                                "kernel", "service_lookup", &result) !=
                STORM_RETURN_SUCCESS || !result)
            {
                return STORM_RETURN_ACCESS_DENIED;
            }

            if (SYSTEM_CALL_ARGUMENTS == 3)
            {
                service_lookup_t *lookup = (service_lookup_t *) SYSTEM_CALL_ARGUMENT_0;
                service_lookup (lookup, (size_t *) SYSTEM_CALL_ARGUMENT_1,
                                (service_t *) SYSTEM_CALL_ARGUMENT_2);
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
            bool result;

            if (capability_has (PROCESS_ID_NONE, dispatch_current_process,
                                "kernel", "service_connect", &result) !=
                STORM_RETURN_SUCCESS || !result)
            {
                return STORM_RETURN_ACCESS_DENIED;
            }

            if (SYSTEM_CALL_ARGUMENTS == 2)
            {
                return_t return_value = service_connect (SYSTEM_CALL_ARGUMENT_0, (service_connection_id_t *) SYSTEM_CALL_ARGUMENT_1);
                
                return return_value;
            }
            else
            {
                return STORM_RETURN_INVALID_ARGUMENT;
            }

            break;
        }

        /* Close a previously opened connection to a service
           provider. */
        case SYSTEM_CALL_SERVICE_CLOSE:
        {
            if (SYSTEM_CALL_ARGUMENTS == 1)
            {
                return_t return_value = service_close (SYSTEM_CALL_ARGUMENT_0);
                return return_value;
            }
            else
            {
                return STORM_RETURN_INVALID_ARGUMENT;
            }
            break;
        }

        /* Invoke a function in a service provider. */
        case SYSTEM_CALL_SERVICE_INVOKE:
        {
            if (SYSTEM_CALL_ARGUMENTS == 3)
            {
                return_t return_value = service_invoke (SYSTEM_CALL_ARGUMENT_0, SYSTEM_CALL_ARGUMENT_1, (void *) SYSTEM_CALL_ARGUMENT_2);
                return return_value;
            }
            else
            {
                return STORM_RETURN_INVALID_ARGUMENT;
            }
            break;
        }

        /* An unsupported system call. */
        default:
        {
            debug_print ("Invalid system call executed: %u\n", SYSTEM_CALL_NUMBER);
            return STORM_RETURN_INVALID_ARGUMENT;
            break;
        }
    }
}
