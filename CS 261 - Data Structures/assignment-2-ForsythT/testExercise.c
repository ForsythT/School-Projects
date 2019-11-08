
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"
#include "stack_exercise.h"

void assertTrue(int predicate, char *message)
{
  printf("%s: ", message);
  if (predicate)
    printf("PASSED\n");
  else
    printf("FAILED\n");
}

void check_modified(DynArr * d){
  int fail = 0;
  for(int i=0;i<10;i++){
    fail |= getDynArr(d,i)==i;
  }
  assertTrue(!fail,"Stack was modified!");
}

int main(int argc, char* argv[]){

  char* t1 = "{}[]()";
  assertTrue(valid_bracket(t1)==1,t1);
  char* t2 = "{][}(]";
  assertTrue(valid_bracket(t2)==0,t2);
  char* t3 = "(([]))";
  assertTrue(valid_bracket(t3)==1,t3);
  char* t4 = "(([]))";
  assertTrue(valid_bracket(t4)==1,t4);
  char* t5 = ")";
  assertTrue(valid_bracket(t5)==0,t5);

  DynArr * d = createDynArr(10);
  for(int i=0;i<10;i++){
    addDynArr(d,i+'a');
  }

  for(int i=0;i<10;i++){
    char * tmp;
    char * tmp2;
    asprintf(&tmp,"Checking %c",i+'a');
    asprintf(&tmp2,"Checking %c",i+'o');

    assertTrue(in_stack(d,i+'a'),tmp);
    assertTrue(!in_stack(d,i+'o'),tmp2);
    check_modified(d);


    free(tmp);
    free(tmp2);
  }





}
