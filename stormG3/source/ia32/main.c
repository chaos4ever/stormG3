/* $chaos: main.c,v 1.24 2002/10/04 19:01:21 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

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
#include <storm/ia32/module.h>
#include <storm/ia32/multiboot.h>
#include <storm/ia32/port.h>
#include <storm/ia32/timer.h>

void main_bootup (int argument_count UNUSED, char *arguments[] UNUSED)
{
    /* Set up the CPU. Detect family, model etc. */
    cpu_init ();

    /* Set up debugging. */
    debug_init ();
    debug_print ("storm %s (compiled by %s on %s %s).\n", STORM_VERSION, CREATOR, __DATE__, __TIME__);

    /* Set up exception handlers. */
    exception_init ();

    /* Set up physical memory allocation. */
    memory_physical_init ();
    debug_print ("Running on a family %d CPU with %d MiB RAM.\n", cpu_info.family, (physical_pages * 4) / 1024);

    /* Set up global memory allocation. */
    memory_global_init ();

    /* Set up virtual memory. */
    memory_virtual_init ();

    /* Set up DMA support. */
    dma_init ();

    /* Set up port support. */
    port_init ();

    /* Set up timer support. */
    timer_init ();

    /* Set up IRQ support. This will also enable interrupts, so the
       dispatcher will be called. */
    irq_init ();

    /* Set up module support. */
    module_init ();

    /* Print a final line of debug information. */
    debug_print ("Free memory after system startup: %u pages\n", free_pages);

    /* We are finished. Pass on to the idle task. */
}
