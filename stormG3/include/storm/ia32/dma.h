/* $chaos: dma.h,v 1.3 2002/06/23 20:08:30 per Exp $ */
/* Abstract: DMA support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_DMA_H__
#define __STORM_IA32_DMA_H__

#include <storm/storm.h>

/* Defines. */
#define NUMBER_OF_CONTROLLERS              2
#define NUMBER_OF_CHANNELS_PER_CONTROLLER  4
#define NUMBER_OF_CHANNELS                 (NUMBER_OF_CONTROLLERS * \
                                           NUMBER_OF_CHANNELS_PER_CONTROLLER)

/* Initialize DMA support. */
extern void dma_init (void);

#endif /* !__STORM_IA32_DMA_H__ */
