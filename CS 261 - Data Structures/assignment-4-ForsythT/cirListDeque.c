#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "structs.h"
#include "cirListDeque.h"


# define TYPE_SENTINEL_VALUE NULL


/* ************************************************************************
    Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
    ************************************************************************ */

/* internal functions interface */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque* q, struct DLink* lnk, TYPE v);
void _removeLink(struct cirListDeque* q, struct DLink* lnk);



/* ************************************************************************
   Deque Functions
   ************************************************************************ */



/* Initialize deque.

   param: qpointer to the deque
   pre:q is not null
   post:q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque* q) {
  q->Sentinel = _createLink(TYPE_SENTINEL_VALUE);
  q->Sentinel->prev = q->Sentinel;
  q->Sentinel->next = q->Sentinel;
  q->size = 0;
}

/*
   create a new circular list deque
*/
struct cirListDeque* createCirListDeque() {
  struct cirListDeque* newCL = malloc(sizeof(struct cirListDeque));
  _initCirListDeque(newCL);
  return(newCL);
}


/* Create a link for a value.

   param: valthe value to create a link for
   pre:none
   post:a link to store the value
*/
struct DLink* _createLink (TYPE val) {
  /* allocate memory for the new link */
  struct DLink* lnk = (struct DLink*) malloc(sizeof(struct DLink));
  assert(lnk != 0);

  lnk->value = val;
  return lnk;
}

/* Adds a link after another link

   param: qpointer to the deque
   param: lnkpointer to the existing link in the deque
   param: vvalue of the new link to be added after the existing link
   pre:q is not null
   pre: lnk is not null
   pre:lnk is in the deque
   post:the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque* q, struct DLink* lnk, TYPE v) {
  /* create the new link */
  struct DLink* newLnk = _createLink(v);

  /* re-allocate pointers */
  newLnk->next = lnk->next;
  newLnk->prev = lnk;
  lnk->next->prev = newLnk;
  lnk->next = newLnk;

  /* increase the size of the deque */
  ++(q->size);
}

/* Adds a link to the back of the deque

   param: qpointer to the deque
   param: valvalue for the link to be added
   pre:q is not null
   post:a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque* q, TYPE val) {
  /* add the link before the Sentinel */
  _addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque

   param: qpointer to the deque
param: valvalue for the link to be added
pre:q is not null
post:a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque* q, TYPE val) {
  /* add the link after the Sentinel */
  _addLinkAfter(q, q->Sentinel, val);
}

/* Get the value of the front of the deque

   param: qpointer to the deque
   pre:q is not null and q is not empty
   post:none
   ret: value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque* q) {
  assert(!isEmptyCirListDeque(q));
  return q->Sentinel->next->value;
}

/* Get the value of the back of the deque

   param: qpointer to the deque
   pre:q is not null and q is not empty
   post:none
   ret: value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque* q) {
  assert(!isEmptyCirListDeque(q));
  return q->Sentinel->prev->value;
}

/* Remove a link from the deque

   param: qpointer to the deque
   param: lnkpointer to the link to be removed
   pre:q is not null and q is not empty
   pre:lnk is in the deque
   post:the link is removed from the deque
*/
void _removeLink(struct cirListDeque* q, struct DLink* lnk) {
  assert(!isEmptyCirListDeque(q));
  lnk->next->prev = lnk->prev;
  lnk->prev->next = lnk->next;
  free(lnk);
  --(q->size);
}

/* Remove the front of the deque

   param: qpointer to the deque
   pre:q is not null and q is not empty
   post:the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque* q) {
  _removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

   param: qpointer to the deque
   pre:q is not null and q is not empty
   post:the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque* q) {
  _removeLink(q, q->Sentinel->prev);
}

/* De-allocate all links of the deque

   param: qpointer to the deque
   pre:none
   post:All links (including the Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque* q) {
  while (!isEmptyCirListDeque(q))
    removeFrontCirListDeque(q);
  free(q->Sentinel);
}

/* Deallocate all the links and the deque itself.

   param: vpointer to the dynamic array
   pre:v is not null
   post:the memory used by v->data is freed
*/
void deleteCirListDeque(struct cirListDeque* q) {
  assert(q != NULL);
  freeCirListDeque(q);
  free(q);
}

/* Check whether the deque is empty

   param: qpointer to the deque
   pre:q is not null
   ret: 1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque* q) {
  return (q->size == 0);
}


/* Print the links in the deque from front to back

   param: qpointer to the deque
   pre:q is not null and q is not empty
   post: the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque* q) {
  struct DLink* lnk;
  assert(!isEmptyCirListDeque(q));
  lnk = q->Sentinel->next;
  do {
    printf("%d->", lnk->value->number);
    lnk = lnk->next;
  } while (lnk != q->Sentinel);

  printf("END\n");
}



// Queue interface
void queueListEnqueue(struct cirListDeque* q, TYPE item){
  addBackCirListDeque(q,item);
}

TYPE queueListDequeue(struct cirListDeque* q){
  TYPE d = frontCirListDeque(q);
  removeFrontCirListDeque(q);
  return d;
}

TYPE queueListFront(struct cirListDeque* q){
  return frontCirListDeque(q);
}


// Stack interface
void stackListPush(struct cirListDeque* q,TYPE item){
  addFrontCirListDeque(q,item);
}

TYPE stackListPop(struct cirListDeque* q){
  TYPE t = frontCirListDeque(q);
  removeFrontCirListDeque(q);
  return t;
}

TYPE stackListTop(struct cirListDeque* q){
  return frontCirListDeque(q);
}
