#include "list.h"

void init(struct list *l){
	l->head = NULL;
	l->tail = NULL;
}

int length(struct list l){
	struct node *temp; //temp node to go through list
	int count; //keeps count of num nodes

	temp = l.head; //start at head
	while(temp != NULL){ //keeps going through until reaching last node
		count++;
		temp = temp->next;
	}
	return count;
}

void print(struct list l){
	struct node *temp; //temp node to go through list

	temp = l.head; //start at head
	printf("List Contents:\n");
	while(temp != NULL){ //keeps going through until reaching last node
		printf("%d ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}

void push_front(struct list *l, int num){
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node)); //allocate space for new node
	
	temp->val = num; //store data
	temp->next = l->head; //set temp next to point at the old head
	temp->prev = NULL;
	l->head = temp; //set temp as head	
	if(l->tail == NULL){
		l->tail = temp;	
	}
	if(temp->next != NULL){
		temp->next->prev = temp; //set next node's (old head) prev as the new head temp
	}	
}

void push_back(struct list *l, int num){ //basically the opposite of push_front
	struct node *temp, *temp2;
	temp = (struct node*)malloc(sizeof(struct node)); 
	
	temp->val = num;
	temp->prev = l->tail;
	temp->next = NULL;
	l->tail = temp;
	if(l->head == NULL){
		l->head = temp;
	}	

	if(temp->prev != NULL){
		temp2 = temp->prev;
		temp2->next = l->tail;
	}
}

void clear(struct list *l){
	struct node *temp; //temp node to go through list

	temp = l->head;
	while(temp->next != NULL){
		temp = temp->next;
		free(temp->prev);
	}
	free(temp);
}

void remove_val(struct list *l, int num){
	struct node *temp, *tnext; //temp node to go through list, tnext to point at the next node incase temp gets freed
	int count = 0; //count if a node was removed

	temp = l->head;
	while(temp != NULL){
		if(temp->next != NULL)
			tnext = temp->next;
		else
			tnext = NULL;
		if(temp->val == num){
			if(temp->next != NULL){ //avoid seg faults
				temp->next->prev = temp->prev; //the next nodes prev now points to the prev node
			}
			if(temp->prev !=NULL){ //avoid seg faults
				temp->prev->next = temp->next; //previous nodes next now points to the next node	
			}
			if(temp == l->head){
				l->head = temp->next;
			}
			if(temp == l->tail){
				l->tail = temp->prev;
			}
			free(temp); //free the memory that was allocated for temp
			count++;
		}
		temp = tnext;
	}
	if(count == 0){
		printf("%d is not inside this list.\n", num);
	}
}

void sort_descending(struct list *l){ //same as ascending but comparing < instead of >
	struct node *temp; //temp node to go through list
	int tswap; //temp node for swapping
	int cont = 1;

	while(cont != 0){
		cont = 0;
		temp = l->head;
		while(temp->next != NULL){
			if(temp->val < temp->next->val){ //only thing different
				tswap = temp->next->val;
				
				temp->next->val = temp->val;

				temp->val = tswap;
				
				cont = 1;
			}
			temp = temp->next;
		}
	}
}

void sort_ascending(struct list *l){
	struct node *temp; //temp node to go through list
	int tswap; //temp int for swapping val;
	int cont = 1;

	while(cont != 0){
		cont = 0;
		temp = l->head; //start temp at head
		while(temp->next != NULL){ //avoid seg faults
			if(temp->val > temp->next->val){ //check swap condition
				tswap = temp->next->val; //swap
				
				temp->next->val = temp->val;

				temp->val = tswap;
			
				cont = 1;
			}
			temp = temp->next; //go to next value
		}
	}
}

void insert(struct list *l, int num, int pos){
	struct node *temp_new, *temp; //temp node to go through list, temp_new is new node
	temp_new = (struct node*)malloc(sizeof(struct node)); //allocate space
	int count = 1, check = 0; //tracking the position, check for seeing if placed

	temp = l->head;
	while(temp != NULL || count == pos){
		if(count == pos && temp != NULL && pos != 1){
			temp_new->val = num;
			temp_new->prev = temp->prev;
			temp_new->next = temp;
			if(temp->prev != NULL){
				temp->prev->next = temp_new;
			}
			temp->prev = temp_new;
			check = 1;
		}
		else if(count == pos && temp == NULL){
			push_back(l, num);
			check = 1;
		}
		else if(count == pos && temp != NULL && pos == 1){
			push_front(l, num);
			check = 1;
		}
		temp = temp->next;
		count++;
	}
	if(check == 0){
		printf("That position is invalid");
		free(temp_new);
	}
}
