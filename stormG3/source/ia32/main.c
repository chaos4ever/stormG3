/* $chaos: main.c,v 1.8 2002/06/11 21:25:48 per Exp $ */
/* Abstract: This is the startup point of storm. It is executed right
   after the assembly language init code has set up the GDT, kernel
   stack, etc. Here, we initialise everything in the storm, like
   IRQ/exception handling, the timer hardware, the memory facilities
   of the host CPU and multitasking. It is also responsible for
   starting the servers loaded by the Multiboot compliant boot
   loader. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING.
   reference documentation. */

#include <storm/config.h>
#include <storm/defines.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/exception.h>
#include <storm/ia32/main.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/multiboot.h>

/* Do the bootup procedure. */
void main_bootup (int argument_count UNUSED, char *arguments[] UNUSED)
{
    /* Set up debugging. */
    debug_init ();
    debug_print ("storm %s (compiled by %s on %s %s).\n", STORM_VERSION, CREATOR, __DATE__, __TIME__);

    /* Initialize the multiboot structures. */
    multiboot_init ();
    
    /* Set up physical memory allocation. */
    memory_physical_init ();

    /* Set up global memory allocation. */
    memory_global_init ();

    /* Set up virtual memory. */
    memory_virtual_init ();

    /* Set up exception handlers. */
    exception_init ();

    /* Test the allocation. */
    {
        void *pointer1 = NULL, *pointer2 = NULL, *pointer3 = NULL;
        return_t return_value;
        return_value = memory_global_allocate (&pointer1, 64);
        debug_print ("[%d, %x] ", return_value, pointer1);

        return_value = memory_global_allocate (&pointer2, 64);
        debug_print ("[%d, %x] ", return_value, pointer2);

        return_value = memory_global_allocate (&pointer3, 64);
        debug_print ("[%d, %x] ", return_value, pointer3);

        return_value = memory_global_deallocate (pointer1);
        debug_print ("[%d] ", return_value);

        return_value = memory_global_deallocate (pointer2);
        debug_print ("[%d] ", return_value);

        return_value = memory_global_allocate (&pointer2, 64);
        debug_print ("[%d, %x] ", return_value, pointer2);

        return_value = memory_global_deallocate (pointer3);
        debug_print ("[%d] ", return_value);

        return_value = memory_global_deallocate (pointer2);
        debug_print ("[%d] ", return_value);
    }

    /* We are finished. Pass on to the idle task. */
}
