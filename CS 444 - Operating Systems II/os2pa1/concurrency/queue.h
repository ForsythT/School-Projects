#pragma once
#include "event.h"
// queue is facing this way: front <---- rear
// dequeue at front
// enqueu at rear
// so we can have less asm instruction for dequeue()
typedef struct Queue Queue;
struct Queue {
    struct Event array[32]; // cap must equal to g_queue_cap
    int front;
    int rear; // rear+1 is num_elements

};
int enqueue(Queue *queue, struct Event new_val);
Event* dequeue(Queue *queue);
void init_array(Event e[]);
void CreateQueue(Queue* queue);
int GetSize(Queue* queue);
int IsEmpty(Queue* queue);
int IsFull(Queue* queue);
void display(FILE* fd, Queue* queue);
