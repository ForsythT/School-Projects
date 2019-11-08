#include <stdio.h>
#include <assert.h>
#include "cirListDeque.h"

#define NUM_TEST_VALUES 16

int main() {

  struct cirListDeque* queue_deque = createCirListDeque();
  struct cirListDeque* stack_deque = createCirListDeque();
  TYPE values[NUM_TEST_VALUES];

  for (int i = 0; i < NUM_TEST_VALUES; i++) {
    values[i] = i;
    queueListEnqueue(queue_deque, i);
    stackListPush(stack_deque, i);
  }

  printf("++ Queue:\n");
  printCirListDeque(queue_deque);

  printf("\n++ Stack:\n");
  printCirListDeque(stack_deque);

  printf("\nChecking queue ordering...\n");
  for (int i = 0; i < NUM_TEST_VALUES; i++) {
    assert(queueListFront(queue_deque) == values[i]);
    assert(queueListDequeue(queue_deque) == values[i]);
  }
  printf("  ... queue is good!\n");

  printf("\nChecking stack ordering...\n");
  for (int i = NUM_TEST_VALUES - 1; i >= 0; i--) {
    assert(stackListTop(stack_deque) == values[i]);
    assert(stackListPop(stack_deque) == values[i]);
  }
  printf("  ... stack is good!\n");

}
