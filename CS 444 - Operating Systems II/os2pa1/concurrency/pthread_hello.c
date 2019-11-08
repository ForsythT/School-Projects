#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "randomizationInterface.h"
#include "queue.h"

//#include "mt.h"
//#include "mersenne.c"

#define PRODUCER 0
#define CONSUMER 1
#define NUM_ARGS 2
//int g_total = 0;

struct args {
	int tid;
};

struct Queue buffer;        //buffer queue
pthread_cond_t signalc, signalp;     //thread signals
pthread_mutex_t lock;					//mutex

/*void *hello(void *arguments)
{
    if (a->thread_type < 5) {
	    sleep(a->sleep_time);
        int tmp_total = g_total;
        g_total = g_total + a->value;
	    return (void*)printf("Hello from thread %ld - PRODUCER! I slept %ld seconds and added %d to g_total! g_total went from %d to %d\n", a->tid, a->sleep_time, a->value, tmp_total, g_total);
    } else {
	    sleep(a->sleep_time);
        int tmp_total = g_total;
        g_total = g_total - a->value;
        return (void*)printf("Hello from thread %ld - CONSUMER! I slept %ld seconds and subtracted %d from g_total! g_total went from %d to %d\n", a->tid, a->sleep_time, a->value, tmp_total, g_total);
    }
}*/

void* produce(void *arg){
	//printf("creating producer\n");
	struct args *a = (struct args*)arg;
    int tid = a->tid;
	while (1){
		pthread_mutex_lock(&lock);     //acquire access to buffer
		struct Event e;
		e.value = getRandom(1, 50);      //create random numbers for event to add to buffer
		e.sleep_time = getRandom(2, 9);
		printf("PRODUCER %d: Produced {%ld, %ld}\n", tid, e.value, e.sleep_time);

		while(IsFull(&buffer)) {           //wait for buffer item to be used by consumer
            printf("PRODUCER %d: Buffer is full, waiting...\n", tid);
			pthread_cond_wait(&signalp, &lock);
        }
		enqueue(&buffer, e);               //push event to buffer
		printf("PRODUCER %d: Pushed {%ld, %ld}\n", tid, e.value, e.sleep_time);
		display(stdout, &buffer);
		pthread_cond_signal(&signalc);      // unblock consumer thread
		//printf("PRODUCER: Signalled to consumer\n");
		pthread_mutex_unlock(&lock);				//unlock mutex

        
		//printf("PRODUCER %d: Start sleeping for %d seconds\n", tid, e.sleep_time);
		e.sleep_time = getRandom(3, 7);
		sleep(e.sleep_time);
	}
}


void* consume(void * arg){
	//printf("creating consumer\n");
	struct args *a = (struct args*)arg;
    int tid = a->tid;
	while(1){
		pthread_mutex_lock(&lock);
		while(IsEmpty(&buffer)){
			printf("CONSUMER %d: Buffer is empty, waiting...\n", tid);
			pthread_cond_wait(&signalc, &lock);
		}
		struct Event *e;
		e = dequeue(&buffer);
		printf("CONSUMER %d: Received {%ld, %ld}\n", tid, e->value, e->sleep_time);
		display(stdout, &buffer);
		pthread_cond_signal(&signalp);
		pthread_mutex_unlock(&lock);

		printf("CONSUMER %d: Working on {%ld, %ld} for %ld seconds\n", tid, e->value, e->sleep_time, e->sleep_time);
		sleep(e->sleep_time);
		printf("CONSUMER %d: Done {%ld, %ld}. Result is %ld\n", tid, e->value, e->sleep_time, e->value);
	}
}

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS + 1) {
        printf("ERROR: You must supply 2 arguments:\n");
        printf("ERROR: Format: ./concurrency <number of producers> <number of consumers>\n");
        exit(1);
    }
    if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
        printf("ERROR: Both arguments must be greater than 0\n");
        exit(1);
    }

	unsigned long init[4] = {0x123, 0x234, 0x345, 0x456};
	unsigned long length = 4;
	init_by_array(init, length);

	CreateQueue(&buffer);
    int num_prods = atoi(argv[1]);
	pthread_t producers[num_prods];
	struct args prod_args[num_prods];
    int num_cons = atoi(argv[2]);
    pthread_t consumers[num_cons];
	struct args cons_args[num_cons];

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&signalc, NULL);
	pthread_cond_init(&signalp, NULL);

    int i;
    for (i = 0; i < num_prods; i += 1) {
		prod_args[i].tid = i;
	    pthread_create(&(producers[i]), NULL, produce, (void*)&prod_args[i]);
    }

    int j;
    for (j = 0; j < num_cons; j += 1) {
        cons_args[j].tid = j;
	    pthread_create(&(consumers[j]), NULL, consume, (void*)&cons_args[j]);
    }

	while(1){
        // do work
	}

    //i = 0;
	//for(i = 0; i < num_prods; i += 1){
	//	pthread_join(producers[i], NULL);
	//}

    //j = 0;
	//for(j = 0; j < num_cons; j += 1){
	//	pthread_join(consumers[j], NULL);
	//}

	return 0;
}
