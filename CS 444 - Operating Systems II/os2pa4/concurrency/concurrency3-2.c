#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


struct buffer_item{
  int data;
  struct buffer_item * next;
};

struct buffer {
  struct buffer_item * head;
  int length;
};

struct buffer buff;
int delete_in_progress;
int search_in_progress;
int insert_in_progress;

pthread_mutex_t s;
pthread_mutex_t i;
pthread_mutex_t d;

void * searcher(){
  pthread_t id = pthread_self();     //get thread's id
  int tid = (int)id;               //typecast to int
  struct buffer_item * itr;
  int count;

  while(1){
  //  if(!pthread_mutex_trylock(&d)){
    while(delete_in_progress){
      sleep(2);
    }
    search_in_progress++;
      printf("Searcher Thread %u has started searching the buffer\n", id);
      sleep(2);
      if(buff.head == NULL){
        printf("Searcher Thread %u says the buffer is empty\n", id);
      }else{
        itr = buff.head;
        count = 0;
        while(itr != NULL){
          itr = itr->next;
          count++;
        }
        printf("Searcher Thread %u says the buffer has %i items\n", id, count);
      }
      search_in_progress--;

    sleep(3);
  }
}

void * inserter(){
  pthread_t id = pthread_self();     //get thread's id
  int tid = (int)id;               //typecast to int
  struct buffer_item * itr;

  while(1){
    if(!pthread_mutex_trylock(&i)){
      while(delete_in_progress){
        sleep(2);
      }
      insert_in_progress = 1;
      struct buffer_item * newitem = (struct buffer_item*)malloc(sizeof(struct buffer_item));
      newitem->data = buff.length; newitem->next = NULL;
      if(buff.head == NULL)
        buff.head = newitem;
      else{
        itr = buff.head;
        while(itr->next != NULL){
          itr = itr->next;
        }
        itr->next = newitem;
        buff.length++;
        printf("Inserter Thread %u inserted item with value %i at buffer tail\n", id, newitem->data);
      }
    pthread_mutex_unlock(&i);
    insert_in_progress = 0;
  }
  sleep(3);
  }
}

void * deleter(){
  pthread_t id = pthread_self();     //get thread's id
  int tid = (int)id;               //typecast to int
  struct buffer_item * itr;
  struct buffer_item * temp;

  while(1){
    if(!pthread_mutex_trylock(&d)){
      while(search_in_progress > 0 || insert_in_progress){
        sleep(2);
      }
      delete_in_progress = 1;
      if(buff.length > 0){
        itr = buff.head;
        while(itr->next != NULL){
          temp = itr;
          itr = itr->next;
        }
        printf("Deleter Thread %u deleted value %d from buffer\n", id, itr->data);
        free(itr);
        temp->next = NULL;
        buff.length--;
      }else
        printf("Deleter Thread %u unable to delete, buffer is empty\n", id);
      delete_in_progress = 0;
      pthread_mutex_unlock(&d);
    }
    sleep(6);
  }
}

int main(){
  int i;
  delete_in_progress = 0;
  insert_in_progress = 0;
  search_in_progress = 0;
  pthread_t searchers[2], inserters[2], deleters[2];
  struct buffer_item * head = (struct buffer_item*)malloc(sizeof(struct buffer_item));
  head->data = 0; head->next = NULL;
  buff.head = head; buff.length = 1;

  for(i = 0; i < 2; i++){
    pthread_create(&searchers[i], NULL, searcher, NULL);
    pthread_create(&inserters[i], NULL, inserter, NULL);
    pthread_create(&deleters[i], NULL, deleter, NULL);
  }

  for(;;){}

  return 0;
}
