/* $chaos: dma.h,v 1.6 2002/10/10 12:20:01 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file        dma.h
 * @brief       DMA support. 
 */

#ifndef __STORM_IA32_DMA_H__
#define __STORM_IA32_DMA_H__

#include <storm/storm.h>

/**
 * @brief       The number of DMA controllers in the system.
 */
#define NUMBER_OF_CONTROLLERS              2

/**
 * @brief       The number of DMA channels per controller.
 */
#define NUMBER_OF_CHANNELS_PER_CONTROLLER  4

/**
 * @brief       The total number of DMA channels.
 */
#define NUMBER_OF_CHANNELS                 (NUMBER_OF_CONTROLLERS * \
                                           NUMBER_OF_CHANNELS_PER_CONTROLLER)

/**
 * @brief       Initialize DMA support. 
 */
extern void dma_init (void);

#endif /* !__STORM_IA32_DMA_H__ */
