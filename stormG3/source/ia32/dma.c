/* $chaos: dma.c,v 1.1 2002/06/12 12:20:35 per Exp $ */
/* Abstract: DMA routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/dma.h>

/* Initialize the DMA support. */
void dma_init ()
{
}

/* Register the given DMA channel. */
return_t dma_register (unsigned int dma_channel, void **dma_buffer)
{
    dma_channel = 0;
    dma_buffer = NULL;
    return STORM_RETURN_NOT_IMPLEMENTED;
}
