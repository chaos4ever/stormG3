/* $chaos: main.c,v 1.13 2002/06/14 12:40:28 per Exp $ */
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
#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/dma.h>
#include <storm/ia32/exception.h>
#include <storm/ia32/irq.h>
#include <storm/ia32/main.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/multiboot.h>

/* FIXME: Move to a separate file, gdb.h perhaps? */
#define BREAKPOINT() asm("   int $3");
extern void serial_init (unsigned short port, unsigned int speed);
extern void set_debug_traps (void);

/* Do the bootup procedure. */
void main_bootup (int argument_count UNUSED, char *arguments[] UNUSED)
{
    /* Set up the CPU. Detect family, model etc. */
    cpu_init ();

    /* Set up debugging. */
    debug_init ();
    debug_print ("storm %s (compiled by %s on %s %s).\n", STORM_VERSION, CREATOR, __DATE__, __TIME__);

    /* Initialize the multiboot structures. */
    multiboot_init ();

    /* Set up exception handlers. */
    exception_init ();

    /* Set up physical memory allocation. */
    memory_physical_init ();

    /* Set up global memory allocation. */
    memory_global_init ();

    /* Set up virtual memory. */
    memory_virtual_init ();

    /* Set up DMA support. */
    dma_init ();

    /* Set up IRQ support. This will also enable interrupts, so the
       dispatcher will be called. */
    irq_init ();

#ifdef GDB_INCLUDE
    serial_init (GDB_PORT, GDB_SPEED);
    set_debug_traps ();
    BREAKPOINT ();
#endif

    /* We are finished. Pass on to the idle task. */
}
