/* $chaos: types.h,v 1.1 2002/07/06 07:58:49 per Exp $ */
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
    /* The block magic cookie. */
    unsigned int magic_cookie;

    /* The function block_read. */
    block_read_t read;

    /* The function block_write. */
    block_write_t write;

    /* The function block_info. */
    block_info_function_t info;
} block_service_t;

#endif /* !__BLOCK_TYPES_H__ */
