//references: https://www.mkssoftware.com/docs/man3/sem_post.3.asp


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//#include "randomizationInterface.h"

struct shared_resource{
  int resource[5];
  sem_t lock;
};

struct shared_resource s = {
  {0, 1, 2, 3, 4}, 0
};

void * process(void * arg){
  pthread_t id = pthread_self();     //get thread's id
  int tid = (int)id;               //typecast to int
  int i;

  while(1){
    int data_value = 0;                                  //value to store "Work" in

    if(sem_trywait(&s.lock) == 0)
      printf("thread %u is doing work\n", tid);
    else{
      printf("thread %u is waiting for access\n", tid);
      sem_wait(&s.lock);
      printf("thread %u is doing work\n", tid);
    }

    for(i = 0; i < 5; i++){                           //simulate doing some work with the resource
      data_value += s.resource[i];
    }
    sleep(2);                                       //allow some time to pass to simulate the thred doing more work
    printf("thread %u is done\n", tid);

    sem_post(&s.lock);

    sleep(2);     //sleep a short time to let other threads access the resource

  }
}


int main(){
  pthread_t p1, p2, p3, p4, p5;

  int semerr = sem_init(&s.lock, 0, 3);
  if(semerr != 0) {printf("sem_init failed!\n");}

  pthread_create(&p1, NULL, process, NULL);
  pthread_create(&p2, NULL, process, NULL);
  pthread_create(&p3, NULL, process, NULL);
  pthread_create(&p4, NULL, process, NULL);
  pthread_create(&p5, NULL, process, NULL);


  for(;;){}

  return 0;
}
