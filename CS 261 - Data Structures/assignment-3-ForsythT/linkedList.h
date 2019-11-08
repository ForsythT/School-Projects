#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#define TYPE int

/* Single link structure */
struct Link {
  TYPE value;
  struct Link* next;
};

struct Link* listInsertionSort(struct Link* head);
struct Link* reverseList(struct Link* head);
struct Link* reverseListRecursive(struct Link* head);

#endif
