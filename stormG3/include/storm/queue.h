/* $chaos: queue.h,v 1.1 2002/05/27 19:08:04 per Exp $ */
/* Abstract: Queue prototypes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

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

/*
 *  Queue container structure
 *
 *  This structure encapsulates a linked list of qentry items.
 */
struct queue
{
  struct qentry *begin, **end;
};

/* Initialize the queue. */
extern struct queue *queue_init(struct queue *q);

/* Access an item without removing it from the queue. */
extern QDATUM *queue_peek(struct queue *q, QDATUM *d);

/* Remove an item from the queue. */
extern QDATUM *queue_remove(struct queue *q, QDATUM *d);

/* Append an item to the queue. */
extern int queue_insert(struct queue *q, QDATUM d);

#endif /* !__STORM_QUEUE_H__ */
