#ifndef __CIRLISTDEQUE_H
#define __CIRLISTDEQUE_H

#define TYPE struct data*

/* Double Link Struture */
struct DLink {
  TYPE value;/* value of the link */
  struct DLink * next;/* pointer to the next link */
  struct DLink * prev;/* pointer to the previous link */
};

/* ************************************************************************
   Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
   ************************************************************************ */

struct cirListDeque {
  int size;/* number of links in the deque */
  struct DLink *Sentinel;/* pointer to the sentinel */
};

struct cirListDeque* createCirListDeque() ;
void initCirListDeque(struct cirListDeque *q);
void deleteCirListDeque(struct cirListDeque *q);

int isEmptyCirListDeque(struct cirListDeque *q);

void addBackCirListDeque(struct cirListDeque *q, TYPE val);
void addFrontCirListDeque(struct cirListDeque *q, TYPE val);

TYPE frontCirListDeque(struct cirListDeque *q);
TYPE backCirListDeque(struct cirListDeque *q);

void removeFrontCirListDeque(struct cirListDeque *q);
void removeBackCirListDeque(struct cirListDeque *q);

void freeCirListDeque(struct cirListDeque *q);

void printCirListDeque(struct cirListDeque *q);

void reverseCirListDeque(struct cirListDeque *q);

#endif
