/* $chaos: queue.h,v 1.2 2002/10/04 19:01:19 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file queue.h
 * @brief Queue functions.
 */

#ifndef __STORM_QUEUE_H__
#define __STORM_QUEUE_H__

#include <storm/avltree.h>

#define QDATUM struct avlnode *

/*
 * Queue item structure
 */
struct qentry
{
  struct qentry *next;
  QDATUM d;
};

/**
 * @brief  Queue container structure
 *
 * This structure encapsulates a linked list of qentry items.
 */
struct queue
{
    struct qentry *begin, **end;
};

/** 
 * @brief Initialize the queue. 
 */
extern struct queue *queue_init(struct queue *q);

/**
 * @brief Access an item without removing it from the queue. 
 */
extern QDATUM *queue_peek(struct queue *q, QDATUM *d);

/**
 * @brief Remove an item from the queue. 
 */
extern QDATUM *queue_remove(struct queue *q, QDATUM *d);

/**
 * @brief Append an item to the queue.
 */
extern int queue_insert(struct queue *q, QDATUM d);

#endif /* !__STORM_QUEUE_H__ */
