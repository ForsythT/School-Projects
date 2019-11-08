all: testExercise testDynArray

testExercise:
	gcc -g -Wall -std=c99 -o exercise dynamicArray.c stack_exercise.c testExercise.c

testDynArray:
	gcc -g -Wall -std=c99 -o testda testDynArray.c dynamicArray.c


clean:
	rm exercise
	rm testda
