/* $chaos: queue.c,v 1.3 2002/05/27 19:08:02 per Exp $ */
/* Abstract: Queue code, used by AVL library. */
/* Author: Per Lundberg <per@chaosdev.org>
           Georg Kraml <georg@purists.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/defines.h>
#include <storm/queue.h>

/*
 *  queue_init: Initialize queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue, or NULL if the user wishes to leave 
 *		it to queue_init to allocate the queue.
 *
 *  Return values:
 *
 *    non-NULL  Queue has been initialized.
 *
 *    NULL	Insufficient memory.
 */
struct queue *queue_init(struct queue *q)
{
  if (q || (q = malloc(sizeof(struct queue))) != NULL) {
    q->begin = NULL;
    q->end = &q->begin;
  }
  return q;
}

/*
 *  queue_insert: append an item to the queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue. It is assumed the queue has been
 *		initialized by a call to queue_init.
 *
 *    d		Item to be appended.
 *
 *  Return values:	
 *
 *    1 	The item has been appended.
 *
 *    0		The item could not be appended. Either the queue 
 *              pointer provided was NULL, or the function was unable 
 *              to allocate the amount of memory needed for a new 
 *              queue item. 	
 */
int queue_insert(struct queue *q, QDATUM d)
{
  if (!q || !(*q->end = malloc(sizeof(struct qentry)))) return 0;
  (*q->end)->d = d;
  (*q->end)->next = NULL;
  q->end = &((*q->end)->next);
  return 1;
}

/*
 *  queue_remove: remove an item from the queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue.
 *
 *    d		Pointer to the QDATUM variable that will hold the datum
 *		corresponding to the queue item.
 *
 *  Return values:
 *
 *    non-NULL	An item has been removed. The variable that d points 
 *              to now contains the datum associated with the item 
 *              in question.
 *		
 *    NULL	No item could be removed. Either the queue pointer 
 *              provided was NULL, or the queue was empty. The memory 
 *              location that d points to has not been modified. 
 */
QDATUM *queue_remove(struct queue *q, QDATUM *d)
{
  struct qentry *tmp;
		
  if (!q || !q->begin) return NULL;
  tmp = q->begin;
  if (!(q->begin = q->begin->next)) q->end = &q->begin;
  *d = tmp->d;
  free(tmp);
  return d;	
}

/*
 *  queue_peek: access an item without removing it from the queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue.
 *
 *    d		Pointer to the QDATUM variable that will hold the datum
 *		associated with the first item in the queue, i. e.,
 *		the item that would be removed had queue_remove been called
 *		instead of queue_peek.
 *
 *  Return values:
 * 
 *    See qremove.
 */
QDATUM *queue_peek(struct queue *q, QDATUM *d)
{
  if (!q || !q->begin) return NULL;
  *d = q->begin->d;
  return d;
}
