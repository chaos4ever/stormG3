/* $chaos: dma.h,v 1.4 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file dma.h
 * @brief Abstract: DMA support. 
 */

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
