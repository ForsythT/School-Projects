#ifndef __CIRLISTDEQUE_H
#define __CIRLISTDEQUE_H

#define TYPE double

/* Double Link Struture */
struct DLink {
  TYPE value;
  struct DLink* next;
  struct DLink* prev;
};

/* ************************************************************************
   Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
   ************************************************************************ */

struct cirListDeque {
  int size;  /* number of links in the deque */
  struct DLink* Sentinel;  /* pointer to the sentinel */
};

struct cirListDeque* createCirListDeque();

int isEmptyCirListDeque(struct cirListDeque* q);

void addBackCirListDeque(struct cirListDeque* q, TYPE val);
void addFrontCirListDeque(struct cirListDeque* q, TYPE val);

TYPE frontCirListDeque(struct cirListDeque* q);
TYPE backCirListDeque(struct cirListDeque* q);

void removeFrontCirListDeque(struct cirListDeque* q);
void removeBackCirListDeque(struct cirListDeque* q);

void freeCirListDeque(struct cirListDeque* q);

void printCirListDeque(struct cirListDeque* q);

void reverseCirListDeque(struct cirListDeque* q);

// Queue interface
void queueListEnqueue(struct cirListDeque* q, TYPE item);
TYPE queueListDequeue(struct cirListDeque* q);
TYPE queueListFront(struct cirListDeque* q);

// Stack interface
void stackListPush(struct cirListDeque* q,TYPE item);
TYPE stackListPop(struct cirListDeque* q);
TYPE stackListTop(struct cirListDeque* q);

#endif
