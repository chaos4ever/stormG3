/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Types used by the block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __BLOCK_TYPES_H__
#define __BLOCK_TYPES_H__

/* A block info holds information about this service provider, with
   function pointers to its functionality. */
typedef struct
{
    /* How big is a block? */
    size_t block_size;

    /* How many blocks do we have? */
    size_t block_count;
} block_info_t;

/* Function prototypes for our functions. */
typedef return_t (*block_read_t)(unsigned int starting_block,
                                 unsigned int blocks, void *output);

typedef return_t (*block_write_t)(unsigned int starting_block,
                                  unsigned int blocks, void *input);

typedef return_t (*block_info_function_t)(block_info_t *block_info);

typedef struct
{
    block_read_t read;
    block_write_t write;
    block_info_function_t info;
} block_service_t;

#endif /* !__BLOCK_TYPES_H__ */
