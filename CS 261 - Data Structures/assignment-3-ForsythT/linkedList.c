#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>


struct Link* listInsertionSort(struct Link* head) {

  /*
   * This function should perform an insertion sort on the list whose head is
   * provided as the function's argument, so that the values in the list are
   * sorted in ascending order, starting at the head.
   *
   * The sort should be done without allocating any new Link structs or any
   * other auxiliary data structures.
   *
   * Return a pointer to the new head of the list.
   */
	//initializing new list to put sorted nodes into
	struct Link *new_list = NULL;
	struct Link *next;
	struct Link *current;
	
	//iterate through the given list and insert them to the new list
	struct Link *cur = head;
	while(cur != NULL){
		//store cur->next for next iteration throught the given list
		next = cur->next;
		//special case for head
		if(new_list == NULL || new_list->value >= cur->value){
			cur->next = new_list;
			new_list = cur;
		}
		else{
			
			//another current variable to go through the new list
			//and find the node before we are to insert the cur node of given
			//list
			current = new_list;
			while(current->next != NULL && current->next->value < cur->value){
				current = current->next;
			}
			cur->next = current->next;
			current->next = cur;
		}	
		cur = next;
	}
	//head points to new list
	head = new_list;
	return head;
}


struct Link* reverseList(struct Link* head) {

  /*
   * This function should iteratively reverse the list whose head is provided
   * as the function's argument.
   *
   * The reversal must be done totally in place, i.e. you may not allocate any
   * new Link structs or any other auxiliary data structures.
   *
   * Return a pointer to the new head of the list.
   */
	//init new list Link, cur iterator, next
	struct Link *new = NULL, *cur = head, *next;
	//go through list and reverse
	while(cur != NULL){
		//store next
		next = cur->next;
		cur->next = new;
		new = cur;
		cur = next;
	}
	//head points to new list
	head = new;
	return head;
}


struct Link* reverseListRecursive(struct Link* head){

  /*
   * Write this function for extra credit.  It should do the exact same thing
   * as reverseList() above, except it should do it recursively instead of
   * iteratively (i.e. no loops allowed).
   *
   * Again, you may not allocate any new Link structs or any other auxiliary
   * data structures.  You may, however, define an auxiliary function to help
   * you do the recursion.
   *
   * Return a pointer to the new head of the list.
   */
	return head;
}
