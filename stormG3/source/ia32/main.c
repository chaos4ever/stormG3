/* $chaos: main.c,v 1.5 2002/05/27 06:22:50 per Exp $ */
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
#include <storm/ia32/main.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/multiboot.h>

/* Do the bootup procedure. */
void main_bootup (int argument_count UNUSED, char *arguments[] UNUSED)
{
    void *pointer1 = NULL, *pointer2 = NULL, *pointer3 = NULL;

    /* Set up debugging. */
    debug_init ();
    debug_print ("storm %s (compiled by %s on %s %s).\n", STORM_VERSION, CREATOR, __DATE__, __TIME__);

    /* Initialize the multiboot structures. */
    multiboot_init ();
    
    /* Set up physical memory allocation. */
    memory_physical_init ();

    /* Test the allocation. */
    debug_print ("Return value: %d", memory_physical_allocate(&pointer1, 1));
    debug_print ("%x\n", pointer1);
    debug_print ("Return value: %d ", memory_physical_allocate(&pointer2, 1));
    debug_print ("%x\n", pointer2);
    debug_print ("Return value: %d ", memory_physical_allocate(&pointer3, 1));
    debug_print ("%x\n", pointer3);
    memory_physical_deallocate(pointer1);
    debug_print ("Return value: %d ", memory_physical_allocate(&pointer1, 1));
    debug_print ("%x\n", pointer1);
    debug_print ("Return value: %d ", memory_physical_allocate(&pointer2, 1));
    debug_print ("%x\n", pointer2);
    debug_print ("Return value: %d ", memory_physical_allocate(&pointer3, 1));
    debug_print ("%x\n", pointer3);

    /* We are finished. Pass on to the idle task. */
}
