#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// queue is facing this way: front <---- rear
// dequeue at front
// enqueu at rear
// so we can have less asm instruction for dequeue()

//int g_queue_cap = 32; // for testing only
#define QUEUE_CAP 32
#define DEFAULT_VAL -999
#define DEQUEUE_FAILED -999

/* @brief initialize all values in queue array to DEFAULT_VAL
 *
 * @param array
 * @param n
 */

void init_array(Event e[]){     //array initialization function
  int i;
  for (i = 0; i < QUEUE_CAP; i+=1){
      e[i].value = DEFAULT_VAL;
      e[i].sleep_time = DEFAULT_VAL;
  }
}


// queue is facing this way: front <---- rear
// dequeue at front
// enqueu at rear
// so we can have less asm instruction for dequeue()

/**
 * @brief get queue and initialize all values in queue array to DEFAULT_VAL.
 *        Set front and rear references to default values.
 *
 * @param queue
 */
void CreateQueue(Queue* queue) {
    init_array(queue->array);
    queue->front = 0;
    queue->rear = -1;
}
/**
 * @brief get queue and initialize all values in queue array to DEFAULT_VAL.
 *        Set front and rear references to default values.
 *        Does the same thing as createQueue
 *
 * @param queue
 */
void DestroyQueue(Queue* queue) {
    init_array(queue->array);
    queue->front = 0;
    queue->rear = -1;
}
/**
 * @brief Get the Size of queue instance
 *
 * @param queue
 * @return int
 */
int GetSize(Queue* queue) {
    return (queue->rear+1);
}
/**
 * @brief if size is zero, queue is empty, else is not empty
 *
 * @param queue
 * @return int
 */
int IsEmpty(Queue* queue) {
    if (GetSize(queue) == 0)
        return 1;
    return 0;
}
/**
 * @brief if queueSize == queueCap then queue is full, else is not full
 *
 * @param queue
 * @return int
 */
int IsFull(Queue* queue) {
    if (GetSize(queue) == QUEUE_CAP)
        return 1;
    return 0;
}

/**
 * @brief adds a new value to queue if queue is not full. If it is, return -1
 *
 * @param queue
 * @param new_val
 * @return int
*/

int enqueue(Queue* queue, struct Event new_val){       //add event to queue
    if (IsFull(queue))
        return -1;                                     //return -1 if full
    queue->rear += 1;
    queue->array[queue->rear] = new_val;
    return 0;                                          //return 0 if no error
}

/**
 * @brief removes value to queue if queue is not empty. If it is, return value DEQUEUE_FAILED
 *
 * @param queue
 * @return int
 */

Event* dequeue(Queue* queue) {
    if (IsEmpty(queue))
       return NULL;
    Event* return_val = malloc(sizeof(Event));
    *(return_val) = queue->array[queue->front];
    int i;
    for (i = queue->front; i < queue->rear; i += 1) {
        queue->array[i] = queue->array[i+1];
    }
    queue->array[queue->rear].value = DEFAULT_VAL;
    queue->array[queue->rear].sleep_time = DEFAULT_VAL;
    queue->rear -= 1;
    return return_val;
}

/**
 * @brief Get the Front object and returns its value
 *
 * @param queue
 * @return Event
 */

Event* GetFront(Queue* queue) {
    return &queue->array[queue->front];
}


/**
 * @brief Get the Rear object and returns its value
 *
 * @param queue
 * @return Event
 */

Event* GetRear(Queue* queue) {
    return &queue->array[queue->rear];
}

/**
 * @brief displays all objects in queue if queue has objects
 *
 * @param fd
 * @param queue
 */
void display(FILE* fd, Queue* queue) {
    if (IsEmpty(queue))
        return;
    fprintf(fd, "\nBUFFER:   ");
    int i;
    for (i = 0; i <= queue->rear; i += 1) {
      //  fprintf(fd, "%d ", queue->array[i]);
        fprintf(fd, "[%d]{%lu, %lu}  ", i, queue->array[i].value, queue->array[i].sleep_time);
        if (i != 0 && i % 8 == 0)
            fprintf(fd, "\n          ");
    }
    fprintf(fd, "\n\n");
}
/**
 * @brief contains various testing print statements to ensure accuracy
 *
 * @return int
 */
// int main() {
//     Queue q;
//     int i;
//     CreateQueue(&q);
//     Event testarray[5];
//     for (i = 0; i < 5; i+=1){     //generate test array of events with unique values
//       testarray[i].value = i;
//       testarray[i].sleep_time = i;
//     }
//     printf("enqueue 0\n");
//     enqueue(&q, testarray[0]);
//     printf("enqueue 1\n");
//     enqueue(&q, testarray[1]);
//     printf("enqueue 2\n");
//     enqueue(&q, testarray[2]);
//     display(stdout, &q);

//     // printf("dequeue: %d\n", dequeue(&q));
//     printf("front: %lu\n", GetFront(&q)->value);
//     printf("rear: %lu\n", GetRear(&q)->value);
//     display(stdout, &q);

//     printf("enqueue 3\n");
//     enqueue(&q, testarray[3]);
//     printf("enqueue 4\n");
//     enqueue(&q, testarray[4]);
//     display(stdout, &q);

//     printf("dequeue: %lu\n", dequeue(&q)->value);
//     printf("front: %lu\n", GetFront(&q)->value);
//     printf("rear: %lu\n", GetRear(&q)->value);
//     display(stdout, &q);
//     return 0;
// }
