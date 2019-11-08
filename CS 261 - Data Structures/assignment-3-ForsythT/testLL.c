#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

#include "linkedList.h"

struct Link* buildLink(int n, int rev, int mod) {
  struct Link* head = (struct Link*)malloc(sizeof(struct Link));
  struct Link* cur = head;

  for (int i = 0; i < n; i++) {
    if (rev)
      cur->value = n - i - 1;
    else
      cur->value = i;

    if (mod)
      cur->value = cur->value % mod;

    if (i + 1 < n)
      cur->next = (struct Link*)malloc(sizeof(struct Link));
    else
      cur->next  = 0;
    cur = cur->next;
  }

  return head;
}

void printLL(struct Link* l,char* s) {
  printf("LL %s: ",s);
  while (l != 0) {
    printf("%d ", l->value);
    l = l->next;
  }
  printf("\n");
}

int main() {
  // We aren't practicing good memory management
  //    here....

  struct Link* l = buildLink(10, 1, 0);
  struct Link* r = listInsertionSort(l);
  printLL(r, "Sort 0-9 mod 4");

  l = buildLink(10, 0, 0);
  r = reverseList(l);
  printLL(r, "Reverse 0-9");

  l = buildLink(10, 1, 0);
  r = reverseList(l);
  printLL(r, "Reverse 9-0");

  r = reverseList(NULL);
  printLL(r, "Reverse null list");

  l = buildLink(1, 0, 0);
  r = reverseList(l);
  printLL(r, "Reverse single element");

  l = buildLink(10, 0, 0);
  r = reverseListRecursive(l);
  printLL(r, "Recursive reverse 0-9");

  r = reverseListRecursive(l);
  r = reverseListRecursive(NULL);
  printLL(r, "Recursive reverse null");

  l = buildLink(1, 0, 0);
  r = reverseListRecursive(l);
  printLL(r, "Recursive reverse single element");

}
