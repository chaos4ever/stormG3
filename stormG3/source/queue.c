/* $chaos: xemacs-script,v 1.6 2002/05/24 17:34:57 per Exp $ */
/* Abstract: Queue code, used by AVL library. */
/* Author: Per Lundberg <per@chaosdev.org>
           Georg Kraml <georg@purists.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

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

/*
 *  qinit: Initialize queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue, or NULL if the user wishes to leave 
 *		it to qinit to allocate the queue.
 *
 *  Return values:
 *
 *    non-NULL  Queue has been initialized.
 *
 *    NULL	Insufficient memory.
 */
struct queue *
qinit(struct queue *q)
{
	if (q || (q = malloc(sizeof(struct queue))) != NULL) {
		q->begin = NULL;
		q->end = &q->begin;
	}
	return q;
}

/*
 *  qinsert: append an item to the queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue. It is assumed the queue has been
 *		initialized by a call to qinit.
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
int
qinsert(struct queue *q, QDATUM d)
{
	if (!q || !(*q->end = malloc(sizeof(struct qentry)))) return 0;
	(*q->end)->d = d;
	(*q->end)->next = NULL;
	q->end = &((*q->end)->next);
	return 1;
}

/*
 *  qremove: remove an item from the queue.
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
QDATUM *
qremove(struct queue *q, QDATUM *d)
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
 *  qpeek: access an item without removing it from the queue.
 *
 *  Parameters:
 *
 *    q		Pointer to a queue.
 *
 *    d		Pointer to the QDATUM variable that will hold the datum
 *		associated with the first item in the queue, i. e.,
 *		the item that would be removed had qremove been called
 *		instead of qpeek.
 *
 *  Return values:
 * 
 *    See qremove.
 */
QDATUM *
qpeek(struct queue *q, QDATUM *d)
{
	if (!q || !q->begin) return NULL;
	*d = q->begin->d;
	return d;
}

