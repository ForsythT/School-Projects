# Assignment #3
**Due 4:59pm on Monday, 10/17/2016**

The goal of this assignment is to have you start working with linked lists and ADTs built on top of linked lists.  Follow the instructions listed in each part below, filling in and augmenting the appropriate places in the provided code, as requested.

## Part I

In the files `linkedList.h` and `linkedList.c`, a simple, null-terminated linked list structure is provided.  Complete the `listInsertionSort()` and `reverseList()` functions.

`listInsertionSort()` should perform an insertion sort on a given list, so that the values are sorted in ascending order starting with the first link in the list.  It should do this without allocating any new links or other auxiliary data structures and return a pointer to the new head of the sorted list.

The `reverseList()` function should reverse the direction of every link within the list and return the new head.  It should do this in place, i.e. without allocating any new links or any other auxiliary data structures.  For example, `reverseList(a)`` where `a` is a pointer to link 1 below

```
a->Link|-------|
       |value:1|
       |-------|->Link|-------|
                      |value:2|
                      |-------|->Link|-------|
                                     |value:3|
                                     |-------|->NULL
```

should return a pointer (call it `x`) to

```
x->Link|-------|
       |value:3|
       |-------|->Link|-------|
                      |value:2|
                      |-------|->Link|-------|
                                     |value:1|
                                     |-------|->NULL
```

You can test your code for Part I using `testLL.c`.

## Part I (Extra credit)

In `reverseListRecursive()`, implement a recursive version of the list reversal function.  To do this, you may not use any `for` or `while` loops, but may define an auxiliary function if you need to. There are tests in `testLL.c` for this recursive function as well.


## Part II

The files `cirListDeque.h` and `cirListDeque.c` define and implement a deque using a circular, doubly-linked list.  There are also prototypes in `cirListDeque.h` and skeleton functions in `cirListDeque.c` for both a queue and a stack built on top of this deque implementation:

```
// Queue interface
void queueListEnqueue(struct cirListDeque* q, TYPE item);
TYPE queueListDequeue(struct cirListDeque* q);
TYPE queueListFront(struct cirListDeque* q);

// Stack interface
void stackListPush(struct cirListDeque* q, TYPE item);
TYPE stackListPop(struct cirListDeque* q);
TYPE stackListTop(struct cirListDeque* q);
```

You should fill out the skeleton functions in `cirListDeque.c` so they respectively implement a queue and a stack.  You can test your code using the provided `testADT.c`.

## Grading criteria

Your assignment will be graded by compiling it on `flip.engr.oregonstate.edu` using the provided `Makefile`, so make sure you have tested your work under those conditions.  If you currently don't have access to `flip`, you should be able to create an ENGR account at https://teach.engr.oregonstate.edu/ (follow the link that says "Create a new account").

Some other requirements:
* You may not change the function signatures (i.e. `void foo(int k)``).
* You may not add or remove files.

The assignment is worth 100 points total.

* Part I: 60 points
  * 30 points: correctly implements `listInsertionSort()`
  * 30 points: correctly implements `reverseList()`
* Part II: 40 points
  * 20 points: correctly implements stack interface to deque
  * 20 points: correctly implements queue interface to deque

## Submission

We'll be using GitHub Classroom for this assignment. You will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at your assignment repo on the github.com (i.e. github.com/OSU-CS261-F16/assignment-3-YourGitHubUsername). If your changes show up there, you can consider your files submitted.
