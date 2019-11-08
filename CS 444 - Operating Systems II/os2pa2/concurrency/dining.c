#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "randomizationInterface.h"

#define THINK_MIN 1
#define THINK_MAX 20
#define EAT_MIN 2
#define EAT_MAX 9
#define LEFTIE 0
#define NUM_THREADS 5

struct args {
	int tid;
};

const char *philo_name[] = {"Aristotle", "Kant", "Plato", "Confucius", "Socrates"};
pthread_mutex_t forks[5];
pthread_mutex_t count; 
int eating_count = 0;
int forks_philo[5] = {5, 5, 5, 5, 5};

void fork_status() {
	int i;
	printf("\n");
	for(i; i < 5; ++i) {
		if(forks_philo[i] < 5){
			printf("FORK %d: Held by %s\n", i, philo_name[forks_philo[i]]);
		}
		else
			printf("FORK %d: On the table\n", i);
	}
}

int left_fork(int tid) {
	return tid;
}

void get_left_fork(int tid) {
	pthread_mutex_lock(&forks[left_fork(tid)]);	
}

int right_fork(int tid) {
	return (tid + 1) % NUM_THREADS;
}

void get_right_fork(int tid) {
	pthread_mutex_lock(&forks[right_fork(tid)]);	
}

void think(int tid) {
	long t = getRandom(THINK_MIN, THINK_MAX);
	printf("\n%s: Think for %ld seconds\n", philo_name[tid], t);
	sleep(t);
}

void get_forks(int tid) {
	if (tid == LEFTIE) { // if this is the leftie philosopher
		get_left_fork(tid);
		forks_philo[tid] = tid;
		printf("\n%s: Picked up left fork\n", philo_name[tid]);
		get_right_fork(tid);
		forks_philo[(tid+1)%5] = tid;
		printf("%s: Picked up right fork\n", philo_name[tid]);
	} else {
		get_right_fork(tid);	
		forks_philo[(tid+1)%5] = tid;
		printf("\n%s: Picked up right fork\n", philo_name[tid]);
		get_left_fork(tid);
		forks_philo[tid] = tid;
		printf("%s: Picked up left fork\n", philo_name[tid]);
	}
	printf("%s: Succesfully picked up both forks\n", philo_name[tid]);
}

void check_in() {
	pthread_mutex_lock(&count);
	eating_count += 1;
	printf("\nWAITER: %d philosopher(s) eating right now\n", eating_count);
	fork_status();
	pthread_mutex_unlock(&count);
}

void check_out() {
	pthread_mutex_lock(&count);
	eating_count -= 1;
	printf("\nWAITER: %d philosopher(s) eating right now\n", eating_count);
	fork_status();
	pthread_mutex_unlock(&count);
}

void eat(int tid) {
	long t = getRandom(EAT_MIN, EAT_MAX);
	printf("\n%s: Start eating for %ld seconds\n", philo_name[tid], t);
	check_in();	
	sleep(t);	
	printf("\n%s: Finish eating for %ld seconds\n", philo_name[tid], t);
	check_out();	
}

void put_left_fork(int tid) {
	pthread_mutex_unlock(&forks[left_fork(tid)]);	
}

void put_right_fork(int tid) {
	pthread_mutex_unlock(&forks[right_fork(tid)]);	
}

void put_forks(int tid) {
	put_right_fork(tid);	
	forks_philo[(tid+1)%5] = 5;
	put_left_fork(tid);
	forks_philo[tid] = 5;
	printf("\n%s: Put down both forks\n", philo_name[tid]);
}

void* dine(void *arg){
	struct args *a = (struct args*)arg;
    int tid = a->tid;
	while (1){
		think(tid);
		get_forks(tid);
		eat(tid);
		put_forks(tid);
	}
}

void init_mutexes() {
	int i;
	for (i = 0; i < 5; i += 1) {
		pthread_mutex_init(&forks[i], NULL);
	}
	pthread_mutex_init(&count, NULL);
}

int main(int argc, char **argv)
{
	unsigned long init[4] = {0x123, 0x234, 0x345, 0x456};
	unsigned long length = 4;
	init_by_array(init, length);

	pthread_t philosophers[NUM_THREADS];
	struct args threads_args[NUM_THREADS];
	init_mutexes();


    int i;
    for (i = 0; i < NUM_THREADS; i += 1) {
		threads_args[i].tid = i;
	    pthread_create(&(philosophers[i]), NULL, dine, (void*)&threads_args[i]);
    }

	while(1){
        // dine until receiving SIGNTERM signal
	}

	return 0;
}
