/* $chaos: dma.c,v 1.5 2002/10/15 18:14:04 per Exp $ */
/* Abstract: DMA routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/dma.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/process.h>

/* Initialize the DMA support. */
void dma_init (void)
{
}

/* Register the given DMA channel. */
return_t dma_register (unsigned int dma_channel, void **dma_buffer)
{
    /* Make sure the DMA channel number is in the acceptable range. */
    if (dma_channel >= NUMBER_OF_CHANNELS)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    /* Allocate some pages. 128 KiB means that 64 KiB will be usable
       -- one full 16-bit segment. We deallocate the rest, of
       course. */
    return memory_physical_allocate (dma_buffer, 32, PROCESS_ID_KERNEL);
}
