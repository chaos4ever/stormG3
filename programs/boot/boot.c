/* $chaos: boot.c,v 1.10 2002/12/03 18:15:35 johannes Exp $ */
/* Abstract: Boot program (somewhat like init in Unix systems). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002, 2006 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <kernel/kernel.h>

void _start (void) NORETURN;
int main (int argc UNUSED, char **argv UNUSED);

char *test = "spam spam spam! ";

void _start (void)
{
    int return_value = main (0, NULL);
    // FIXME: Implement that system call.. :-)
    //system_call_exit (return_value);
    // The rest of the code is never reached.
    while (TRUE);
}

/* Main function. */
int main (int argc UNUSED, char **argv UNUSED)
{
    size_t services = 1;
    service_t service_list;
    service_lookup_t service_lookup = 
        {
            "kernel", NULL, NULL, NULL, NULL,
            KERNEL_PROTOCOL_MAJOR_VERSION,
            KERNEL_PROTOCOL_MINOR_VERSION
        };
    service_connection_id_t connection_id;

    if (system_call_service_lookup (&service_lookup, &services, &service_list) != STORM_RETURN_SUCCESS)
    {
        return -1;
    }

    if (system_call_service_connect (service_list.id, &connection_id) != STORM_RETURN_SUCCESS)
    {
        return -1;
    }
    
    if (system_call_service_invoke (connection_id, KERNEL_FUNCTION_LOG,
                                    test) != STORM_RETURN_SUCCESS)
    {
        return -1;
    }
    
    if (system_call_service_close (connection_id))
    {
        return -1;
    }

    /* All hail king Jesus. */
    return 0;
}
