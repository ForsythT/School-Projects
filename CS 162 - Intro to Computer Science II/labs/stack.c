#include <stdio.h>
#include <stdlib.h>

struct stack{
	int *contents;
	int top;
	int size;
};

void init(struct stack*);
void push(struct stack*, int);
int pop(struct stack*);
int peek(struct stack);
void destroy(struct stack*);
int empty(struct stack);
int size(struct stack*);

void init(struct stack* s){
	s->contents = '\0';
	s->size = 0;
}

void push(struct stack* s, int num){
	int *temp, i, j;
	i = 0;
	j = 0;
	if(s->contents == '\0')
		s->top = num;

	if(s->contents != '\0'){
		temp = malloc(sizeof(int)*(s->size));
		for(i; i < s->size; i++){
			temp[i] = s->contents[i];
			}
	}
	free(s->contents);
	s->contents = malloc(sizeof(int)*(s->size));
	s->size++;
	if(temp != '\0'){
		for(j; j < (s->size)-1; j++){
			s->contents[j] = temp[j];
		}
	}
	if(s->contents == '\0')
		s->contents[0] = num;
	else
		s->contents[s->size-1] = num;
}


int pop(struct stack* s){
	int *temp, i, t, j;
	j = 0;
	i = 1;
	if(s->contents == '\0')
		return 0;
	t = s->top;
	s->size--;
	temp = malloc(sizeof(int)*s->size);
	for(i; i < s->size+1; i++){
		temp[i-1] = s->contents[i];
	}
	free(s->contents);
	s->contents = temp;
	s->top = s->contents[0];
	return t;
}

int peek(struct stack s){
	return s.top;
}

void destroy(struct stack* s){
	free(s->contents);
}

int empty(struct stack s){
	if(s.contents == '\0')
		return 1;
	else 
		return 0;
}

int size(struct stack *s){
	return s->size;
}

int main(){
	struct stack s;
	int i, p;
	i = 1;
	init(&s);
	push(&s, 5);
	printf("Num: %d\n", s.top);
	push(&s, 10);
	push(&s, 15);
	printf("Top: %d\n", peek(s));
	for(i; i < s.size; i++){
		printf("Num %d: %d\n", i+1, s.contents[i]);
	}
	i = 0;
	printf("Size: %d\n", size(&s));
	p = pop(&s);
	printf("%d\n", p);
	i = 0;
	for(i; i < s.size; i++){
		printf("Num %d: %d\n", i+1, s.contents[i]);
	}
	destroy(&s);
	return 0;
}
