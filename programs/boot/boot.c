/* $chaos: boot.c,v 1.3 2002/10/27 20:30:05 per Exp $ */
/* Abstract: Boot program (somewhat like init in Unix systems). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <kernel/kernel.h>

void _start (void) NORETURN;
int main (int argc UNUSED, char **argv UNUSED);

char *test = "spam spam spam!";

void _start (void)
{
   main (0, NULL);
   // syscall_exit (0);
   while (TRUE);
}


/* Main function. */
int main (int argc UNUSED, char **argv UNUSED)
{
    size_t services;
    service_t *service_list;
    service_lookup_t service_lookup = 
        {
            "kernel", NULL, NULL, NULL, KERNEL_SERVICE_MAJOR_VERSION,
            KERNEL_SERVICE_MINOR_VERSION
        };
    service_connection_id_t connection_id;

    system_call_service_lookup (&service_lookup, &services, &service_list);
    system_call_service_connect (service_list[0].id, &connection_id);
    //    system_call_service_invoke (&connection_id, KERNEL_FUNCTION_DEBUG_PRINT,
    //                                test);
    //    system_call_service_close (connection_id);
    return 0;
}
