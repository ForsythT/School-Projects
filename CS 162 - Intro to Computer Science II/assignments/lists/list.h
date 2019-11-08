#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int val;
	struct node *next;
	struct node *prev;
};

struct list{
	struct node *head;
	struct node *tail;
};


void init(struct list*);		//initialize list
int length(struct list); 		//retun number of nodes in list
void print(struct list); 		//print the values in list
void push_front(struct list *, int); 	//push to front of list
void push_back(struct list *, int); 	//push to end of list

void clear(struct list *); 		//remove all nodes from list
void remove_val(struct list *, int); 	//remove nodes w/ int as val
void sort_ascending(struct list *);
void sort_descending(struct list *);

//insert into a location in the list, start at 0 for front
void insert(struct list *, int, int);
