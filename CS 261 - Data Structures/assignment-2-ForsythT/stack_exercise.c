#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"


int in_stack(DynArr * s,char tofind){
  /*
     Returns 1 if the element `tofind` is present in DynArr `s`, 0
     otherwise.  Upon returning `s` should have its elements in the
     same order as when the function is called. In other words, you
     may modify `s` but must return it to its original state

     You may only call the following funcitons

        DynArr *createDynArr(int cap);
        int isEmptyDynArr(DynArr *v);
        void pushDynArr(DynArr *v, TYPE val);
        TYPE topDynArr(DynArr *v);
        void popDynArr(DynArr *v);

     Hint: use another stack to hold elements while you search
     and then restore the initial state of `s`
  */
	/*int i;

	for(i = 0; i < s->size; i++){
		if(s->data[i] == tofind){
			return 1;
		}
	}*/
	int i;
	struct DynArr* a = createDynArr(s->capacity);
	a->size = s->size;
	a->capacity = s->capacity;
	for(i = 0; i < s->size; i++){
		pushDynArr(a, s->data[i]);
	}
	for(i = 0; i < a->size; i++){
		if(isEmptyDynArr(a) != 1){
			if(topDynArr(a) == tofind){
				return 1;
			}
			popDynArr(a);
		}
	}	

	return 0;
}


int valid_bracket(char * str){
  /*
    str contains only bracking characters - parenthesis ( '(' and ')'
    ), square brackets ('[' and ']') and squiggly brackets ('{' and
    '}')

    This function returns 1 if str contains a set of balanced
    bracketing characters and zero otherwise.  A string is said to
    have balanced bracketing characters if each opening bracket ( '(',
    '{' and '[') contains a correspodning closing bracket
    (')','}',']') of the same type and brackets are closed in the
    reverse order that they are opened.

    For example

    valid_bracket("{}[]()") returns 1
    valid_bracket("{][}(]") returns 0, the brackets do not match
    valid_bracket("(([]))") returns 1
    valid_bracket("(([)])") returns 0,
          because the '(' at index 1 is closed by the ')' at index 3
	  before the '[' at index 2 is closed

    valid_bracket("}") returns 0 because there is no opening bracket for '{'

    valid_bracket("({}[])") returns 1
    valid_bracket("({}([]))") returns 1
    valid_bracket("({}([]){([])})") returns 1
    valid_bracket("({([]))") returns 0

  */
	int i, j;
	int val = 0;
	float len = 0;
	for(i = 0; i < strlen(str); i++){
		if(str[i] == '('){
			if(str[i+1] == ')'){
				val += 1;
			}
			else{	
				for(j = i+1; j < strlen(str); j+=2){
					if(str[j] == ')'){
						val += 1;;
					}
				}
			}
		}
		if(str[i] == '{'){
			if(str[i+1] == '}'){
				val += 1;
			}
			else{
				for(j = i+1; j < strlen(str); j+=2){
					if(str[j] == '}'){
						val += 1;;
					}
				}
			}
		}
		if(str[i] == '['){
			if(str[i+1] == ']'){
				val += 1;
			}
			else{
				for(j = i+1; str[j] != '\0'; j++){
					if(str[j] == ']'){
						val += 1;;
					}
				}
			}
		}
		len++;
	}
	if(val == (len/2)){
		return 1;
	}
	return 0;
}
