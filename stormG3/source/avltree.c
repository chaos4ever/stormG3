/* $chaos: avltree.c,v 1.2 2002/05/27 11:48:15 per Exp $ */
/* Abstract: AVL tree implementation. */
/* Author: Per Lundberg <per@chaosdev.org>
   Georg Kraml <georg@purists.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/avltree.h>
#include <storm/queue.h>

/*
 *  avl_rotate_left: perform counterclockwise rotation
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node
 */
static void avl_rotate_left(struct avlnode **n)
{
  struct avlnode *tmp = *n;

  *n = (*n)->right;
  tmp->right = (*n)->left;
  (*n)->left = tmp;
}

/*
 *  avl_rotate_right: perform clockwise rotation
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node
 */
static void avl_rotate_right(struct avlnode **n)
{
  struct avlnode *tmp = *n;

  *n = (*n)->left;
  tmp->left = (*n)->right;
  (*n)->right = tmp;
}

/*
 *  avl_left_grown: helper function for avl_insert
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node. This node's left 
 *                subtree has just grown due to item insertion; its 
 *                "skew" flag needs adjustment, and the local tree 
 *                (the subtree of which this node is the root node) may 
 *                have become unbalanced.
 *
 *  Return values:
 *
 *    OK          The local tree could be rebalanced or was balanced 
 *                from the start. The parent activations of the avl_insert 
 *                activation that called this function may assume the 
 *                entire tree is valid.
 *
 *    BALANCE     The local tree was balanced, but has grown in height.
 *                Do not assume the entire tree is valid.
 */
static enum AVLRES avl_left_grown(struct avlnode **n)
{
  switch ((*n)->skew) {
    case LEFT:
      if ((*n)->left->skew == LEFT) {
        (*n)->skew = (*n)->left->skew = NONE;
        avl_rotate_right(n);
      }	
      else {
        switch ((*n)->left->right->skew) {
          case LEFT:
            (*n)->skew = RIGHT;
            (*n)->left->skew = NONE;
            break;

          case RIGHT:
            (*n)->skew = NONE;
            (*n)->left->skew = LEFT;
            break;

          default:
            (*n)->skew = NONE;
            (*n)->left->skew = NONE;
        }
        (*n)->left->right->skew = NONE;
        avl_rotate_left(& (*n)->left);
        avl_rotate_right(n);
      }
      return OK;

    case RIGHT:
      (*n)->skew = NONE;
      return OK;
	
    default:
      (*n)->skew = LEFT;
      return BALANCE;
  }
}

/*
 *  avl_right_grown: helper function for avl_insert
 *
 *  See avl_left_grown for details.
 */
static enum AVLRES avl_right_grown(struct avlnode **n)
{
  switch ((*n)->skew) {
    case LEFT:					
      (*n)->skew = NONE;
      return OK;

    case RIGHT:
      if ((*n)->right->skew == RIGHT) {	
        (*n)->skew = (*n)->right->skew = NONE;
        avl_rotate_left(n);
      }
      else {
        switch ((*n)->right->left->skew) {
          case RIGHT:
            (*n)->skew = LEFT;
            (*n)->right->skew = NONE;
            break;

          case LEFT:
            (*n)->skew = NONE;
            (*n)->right->skew = RIGHT;
            break;

          default:
            (*n)->skew = NONE;
            (*n)->right->skew = NONE;
        }
        (*n)->right->left->skew = NONE;
        avl_rotate_right(& (*n)->right);
        avl_rotate_left(n);
      }
      return OK;

    default:
      (*n)->skew = RIGHT;
      return BALANCE;
  }
}

/*
 *  avl_insert: insert a node into the AVL tree.
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node.
 *
 *    d           Item to be inserted.
 *
 *  Return values:
 *
 *    nonzero     The item has been inserted. The excact value of 
 *                nonzero yields is of no concern to user code; when
 *                avl_insert recursively calls itself, the number 
 *                returned tells the parent activation if the AVL tree 
 *                may have become unbalanced; specifically:
 *
 *      OK        None of the subtrees of the node that n points to 
 *                has grown, the AVL tree is valid.
 *
 *      BALANCE   One of the subtrees of the node that n points to 
 *                has grown, the node's "skew" flag needs adjustment,
 *                and the AVL tree may have become unbalanced.
 *
 *    zero        The datum provided could not be inserted, either due 
 *                to AVLKEY collision (the tree already contains another
 *                item with which the same AVLKEY is associated), or
 *                due to insufficient memory.
 */   
enum AVLRES avl_insert(struct avlnode **n, AVLDATUM d)
{
  enum AVLRES tmp;

  if (!(*n)) {
    if (!((*n) = malloc(sizeof(struct avlnode)))) {
      return ERROR;
    }
    (*n)->left = (*n)->right = NULL;
    (*n)->d = d;
    (*n)->skew = NONE;
    return BALANCE;
  }
	
  if (AVLKEY(d) < AVLKEY((*n)->d)) {
    if ((tmp = avl_insert(& (*n)->left, d)) == BALANCE) {
      return avl_left_grown(n);
    }
    return tmp;
  }
  if (AVLKEY(d) > AVLKEY((*n)->d)) {
    if ((tmp = avl_insert(& (*n)->right, d)) == BALANCE) {
      return avl_right_grown(n);
    }
    return tmp;
  }
  return ERROR;
}

/*
 *  avl_left_shrunk: helper function for avl_remove and avl_find_lowest
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node. The node's left
 *                subtree has just shrunk due to item removal; its
 *                "skew" flag needs adjustment, and the local tree
 *                (the subtree of which this node is the root node) may
 *                have become unbalanced.
 *
 *   Return values:
 *
 *    OK          The parent activation of the avl_remove activation
 *                that called this function may assume the entire
 *                tree is valid.
 *
 *    BALANCE     Do not assume the entire tree is valid.
 */                
static enum AVLRES avl_left_shrunk(struct avlnode **n)
{
  switch ((*n)->skew) {
    case LEFT:
      (*n)->skew = NONE;
      return BALANCE;

    case RIGHT:
      if ((*n)->right->skew == RIGHT) {
        (*n)->skew = (*n)->right->skew = NONE;
        avl_rotate_left(n);
        return BALANCE;
      }
      else if ((*n)->right->skew == NONE) {
        (*n)->skew = RIGHT;
        (*n)->right->skew = LEFT;
        avl_rotate_left(n);
        return OK;
      }
      else {
        switch ((*n)->right->left->skew) {
          case LEFT:
            (*n)->skew = NONE;
            (*n)->right->skew = RIGHT;
            break;

          case RIGHT:
            (*n)->skew = LEFT;
            (*n)->right->skew = NONE;
            break;

          default:
            (*n)->skew = NONE;
            (*n)->right->skew = NONE;
        }
        (*n)->right->left->skew = NONE;
        avl_rotate_right(& (*n)->right);
        avl_rotate_left(n);
        return BALANCE;
      }

    default:
      (*n)->skew = RIGHT;
      return OK;
  }
}

/*
 *  avl_right_shrunk: helper function for avl_remove and avl_find_highest
 *
 *  See avl_left_shrunk for details.
 */
static enum AVLRES avl_right_shrunk(struct avlnode **n)
{
  switch ((*n)->skew) {
    case RIGHT:
      (*n)->skew = NONE;
      return BALANCE;

    case LEFT:
      if ((*n)->left->skew == LEFT) {
        (*n)->skew = (*n)->left->skew = NONE;
        avl_rotate_right(n);
        return BALANCE;
      }
      else if ((*n)->left->skew == NONE) {
        (*n)->skew = LEFT;
        (*n)->left->skew = RIGHT;
        avl_rotate_right(n);
        return OK;
      }
      else {
        switch ((*n)->left->right->skew) {
          case LEFT:
            (*n)->skew = RIGHT;
            (*n)->left->skew = NONE;
            break;

          case RIGHT:
            (*n)->skew = NONE;
            (*n)->left->skew = LEFT;	
            break;
			
          default:
            (*n)->skew = NONE;
            (*n)->left->skew = NONE;
        }
        (*n)->left->right->skew = NONE;
        avl_rotate_left(& (*n)->left);
        avl_rotate_right(n);
        return BALANCE;
      }

    default:
      (*n)->skew = LEFT;
      return OK;
  }
}

/*
 *  avl_find_highest: replace a node with a subtree's highest-ranking item.
 *
 *  Parameters:
 *
 *    target      Pointer to node to be replaced.
 *
 *    n           Address of pointer to subtree.
 *
 *    res         Pointer to variable used to tell the caller whether
 *                further checks are necessary; analog to the return
 *                values of avl_left_grown and avl_left_shrunk (see there). 
 *
 *  Return values:
 *
 *    1           A node was found; the target node has been replaced.
 *
 *    0           The target node could not be replaced because
 *                the subtree provided was empty.
 *
 */
static int avl_find_highest(struct avlnode *target, struct avlnode **n, 
                            enum AVLRES *res)
{
  struct avlnode *tmp;

  *res = BALANCE;
  if (!(*n)) {
    return 0;
  }
  if ((*n)->right) {
    if (!avl_find_highest(target, &(*n)->right, res)) {
      return 0;
    }
    if (*res == BALANCE) {
      *res = avl_right_shrunk(n);
    }
    return 1;
  }
  target->d  = (*n)->d;
  tmp = *n;
  *n = (*n)->left;
  free(tmp);
  return 1;
}

/*
 *  avl_find_lowest: replace node with a subtree's lowest-ranking item.
 *
 *  See avl_find_highest for the details.
 */
static int avl_find_lowest(struct avlnode *target, struct avlnode **n,
                    enum AVLRES *res)
{
  struct avlnode *tmp;

  *res = BALANCE;
  if (!(*n)) {
    return 0;
  }
  if ((*n)->left) {
    if (!avl_find_lowest(target, &(*n)->left, res)) {
      return 0;
    }
    if (*res == BALANCE) {
      *res =  avl_left_shrunk(n);
    }
    return 1;
  }
  target->d = (*n)->d;
  tmp = *n;
  *n = (*n)->right;
  free(tmp);
  return 1;
}

/*
 *  avl_remove: remove an item from the tree.
 *
 *  Parameters:
 *
 *    n           Address of a pointer to a node.
 *
 *    key         AVLKEY of item to be removed.
 *
 *  Return values:
 *
 *    nonzero     The item has been removed. The exact value of 
 *                nonzero yields if of no concern to user code; when
 *                avl_remove recursively calls itself, the number
 *                returned tells the parent activation if the AVL tree
 *                may have become unbalanced; specifically:
 *
 *      OK        None of the subtrees of the node that n points to
 *                has shrunk, the AVL tree is valid.
 *
 *      BALANCE   One of the subtrees of the node that n points to
 *                has shrunk, the node's "skew" flag needs adjustment,
 *                and the AVL tree may have become unbalanced.
 *
 *   zero         The tree does not contain an item yielding the
 *                AVLKEY value provided by the caller.
 */
enum AVLRES avl_remove(struct avlnode **n, int key)
{
  enum AVLRES tmp = BALANCE;

  if (!(*n)) {
    return ERROR;
  }
  if (key < AVLKEY((*n)->d)) {
    if ((tmp = avl_remove(& (*n)->left, key)) == BALANCE) {
      return avl_left_shrunk(n);
    }
    return tmp;
  }
  if (key > AVLKEY((*n)->d)) {
    if ((tmp = avl_remove(& (*n)->right, key)) == BALANCE) {
      return avl_right_shrunk(n);
    }
    return tmp;
  }
  if ((*n)->left) {
    if (avl_find_highest(*n, &((*n)->left), &tmp)) {
      if (tmp == BALANCE) {
        tmp = avl_left_shrunk(n);
      }
      return tmp;
    }
  }
  if ((*n)->right) {
    if (avl_find_lowest(*n, &((*n)->right), &tmp)) {
      if (tmp == BALANCE) {
        tmp = avl_right_shrunk(n);
      }
      return tmp;
    }
  }
  free(*n);
  *n = NULL;
  return BALANCE;
}

/*
 *  avl_access: retrieve the datum corresponding to a given AVLKEY.
 *
 *  Parameters:
 *
 *    n           Pointer to the root node.
 *
 *    key         TKEY of item to be accessed.
 *
 *  Return values:
 *
 *    non-NULL    An item yielding the AVLKEY provided has been found,
 *                the return value points to the AVLKEY attached to it.
 *
 *    NULL        The item could not be found.
 */
AVLDATUM *avl_access(struct avlnode *n, int key)
{
  if (!n) {
    return NULL;
  }
  if (key < AVLKEY((n)->d)) {
    return avl_access(n->left, key);
  }
  if (key > AVLKEY((n)->d)) {
    return avl_access(n->right, key);
  }
  return &(n->d);
}

/*
 *  avl_depth_first: depth-first tree traversal.
 *
 *  Parameters:
 *
 *    n          Pointer to the root node.
 *
 *    f          Worker function to be called for every node.
 *
 *    param      Additional parameter to be passed to the
 *               worker function
 *
 *    depth      Recursion depth indicator. Allows the worker function
 *               to determine how many levels the node being processed
 *               is below the root node. Can be used, for example,
 *               for selecting the proper indentation width when
 *               avl_depth_first ist used to print a tree dump to
 *               the screen.
 *
 *               Most of the time, you will want to call avl_depth_first
 *               with a "depth" value of zero.
 */
void avl_depth_first(struct avlnode *n, AVLWORKER *f, int param, int depth)
{
  if (!n) return;
  avl_depth_first(n->left, f, param, depth + 1);
  (*f)(n, param, depth);
  avl_depth_first(n->right, f, param, depth +1);
}

/*
 *  avl_breadth_first: breadth-first tree traversal.
 * 
 *  See avl_depth_first for details.
 */
void avl_breadth_first(struct avlnode *n, AVLWORKER *f, int param)
{
  struct queue q;

  if (!n) return;
  queue_init(&q);
  queue_insert(&q, n);
  while (queue_remove(&q, &n)) {
    (*f)(n, param, 0);
    if (n->left) queue_insert(&q, n->left);
    if (n->right) queue_insert(&q, n->right);
  }
}
