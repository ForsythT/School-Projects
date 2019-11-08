/* CS261- Assignment 1 - Q.1*/
/* Name: Tim Forsyth
 * Date: 9/28/2016
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
 	int id;
  	int score;
};

struct student* allocate() {
  	/* Allocate memory for ten students */
     	struct student *s = malloc(10 *(sizeof(struct student)));
  	/* return the pointer */
	return s;
}


void generate(struct student* students) {
  	/*
   	* Generate random ID and scores for 10 students, ID being between
   	* 0 and 9, scores equal to (id * 10) % 50.
   	*/
	int i;
	for(i = 0; i < 10; i++){
		students[i].id = i;
		students[i].score = (10*i)%50;
	}
}

void output(struct student* students) {
  	/*
   	* Output information about the ten students in the format:
   	*
   	*   ID0 Score0
   	*   ID1 score1
   	*   ID2 score2
   	*   ...
   	*   ID9 score9
   	*/
	int i;
	for(i = 0; i < 10; i++){
		printf("ID%d Score%d\n", students[i].id, students[i].score);
	}
}

int min(struct student* students) {
  	/* return the minimum score */
	int i;
	int min;
	if(students != NULL){
		for(i = 0; i < 10; i++){
			if(i > 0){
				if(students[i].score < students[i-1].score){
					min = students[i].score;
				}
			}
			else{
				min = students[i].score;
			}
		}
	}
	return min;
}

float avg(struct student* students) {
  	/* return the average score */
	int i;
	float avg = 0;
	if(students != NULL){
		for(i = 0; i < 10; i++){
			avg = students[i].score + avg;
		}
	}
	avg = avg/10;
	return avg;	
}

void sort(struct student* students){ 
  	/* return the average score */
	int i;
	struct student temp;
	int cont = 1;
	while(cont == 1){
		cont = 0;
		if(students != NULL){
			for(i = 0; i < 10; i++){
				if(i > 0){
					if(students[i].score > students[i-1].score){
						temp = students[i];
						students[i] = students[i-1];
						students[i-1] = temp;
						cont = 1;			
					}
				}
			}
		}
	}
}

void deallocate(struct student* stud) {
  	/* Deallocate memory from stud */
	if(stud != NULL){
		free(stud);
	}
}

int main(){
  	struct student* stud = allocate();
  	generate(stud);
  	output(stud);
  	sort(stud);
	int i;
  	for (i = 0; i<10; i++) {
   		printf("%d %d\n", stud[i].id, stud[i].score);
  	}	
  	printf("Avg: %f \n", avg(stud));
  	printf("Min: %d \n", min(stud));
  	deallocate(stud);
	return 0;
}
