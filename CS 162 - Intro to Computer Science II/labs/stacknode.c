#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node *next;
};

struct stack{
	struct node *head;
	struct node *tail;
};

void init(struct stack*);
void push(struct stack*, int);
int pop(struct stack*);
void delete(struct stack*);

int length(struct stack l){
	struct node *temp; //temp node to go through list
	int count; //keeps count of num nodes

	temp = l.head;
	while(temp != NULL){
		count++;
		temp = temp->next;
	}
	return count;
}

int main(){
	struct stack s;
	struct node *temp;
	int len;

	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 2);
	push(&s, 2);
	push(&s, 2);
	push(&s, 3);
	len = length(s);
	printf("%d\n", len);

	temp = s.head;
	while(temp != NULL){
		printf("Number: %d\n", temp->val);
		temp = temp->next;
	}
	int p; 
	p = pop(&s);
	printf("%d, %d, %d\n", s.head->val, s.tail->val, p);
	temp = s.head;
	while(temp != NULL){
		delete(&s);
		temp = s.head;
	}
	return 0;
}

void init(struct stack *s){
	s->head = NULL;
	s->tail = NULL;
}

void push(struct stack *s, int num){
	struct node *temp, *temp1;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->val = num;
	temp->next = NULL;
	if(s->head == NULL){
		s->head = temp;
	}
	else{
		temp1 = s->head;
		while(temp1->next != NULL){
			temp1 = temp1->next;
		}
		temp1->next = temp;
	}
	s->tail = temp;
}

void delete(struct stack *s){
	struct node *temp, *old_temp;
	if(s->head == NULL)
		printf("Empty list.\n");
	else if(s->head->next != NULL){
		temp = s->head;
		while(temp->next != NULL){
			old_temp = temp;
			temp = temp->next;
		}
		old_temp->next = NULL;
		free(temp);
		s->tail = old_temp;
	}
	else{
		temp = s->head;
		s->head = NULL;
		free(temp);
	}
}

int pop(struct stack *s){
	int num;
	struct node *temp, *old_temp;
	if(s->head == NULL){
		printf("Empty list.\n");
		return 0;
	}
	else if(s->head->next != NULL){
		num = s->tail->val;
		temp = s->head;
		while(temp->next != NULL){
			old_temp = temp;
			temp = temp->next;
		}
		old_temp->next = NULL;
		free(temp);
		s->tail = old_temp;
	}
	else{
		num = s->tail->val;
		temp = s->head;
		s->head = NULL;
		free(temp);
	}
	return num;
}
