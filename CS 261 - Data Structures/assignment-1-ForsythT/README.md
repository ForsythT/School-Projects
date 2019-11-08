# Assignment #1

**Due at 4:59pm on Monday, 10/3/2016**

There are two parts to this assignment: `Q0.c` and `Q1.c`.  You are given a skeleton file for each part.  Your job is to fill in the missing parts of the skeleton, as specified below.

## `Q0.c`

Write a program (in `Q0.c`) to do the following:

1. In `main()`, declare an integer `x`. Print the address of `x` (using the address-of operator). Pass `x` as an argument to a function `void fooA(int* iptr)`. (Hint: can you pass x itself directly?)

2. In `fooA(int* iptr)`, print the value of the integer pointed to by `iptr`, the address pointed to by `iptr`, and the address of `iptr` itself.

3. In the main function, following the call to `fooA(...)` , print the value of `x`.

4. Implement function `int fooB(int* a, int *b, int c)` which should perform the following computations:

  * Assign `a + b` to `c`. 
  * Set the value pointed to by `a` to the value pointed to by `b`.
  * Set the value pointed to by `b` to double its original value.
  * Return the value of `c`.

## `Q1.c`

Write a program (in `Q1.c`) in which you consider the following structure:

```
struct student {
    int id;
    int score;
};
```

Implement the following functions and demonstrate their functionality using the calls already existing in `main()`:

1. Write a function `struct student* allocate()` that allocates a contiguous chunk of memory for 10 students and returns the pointer.

2. Write a function `void generate(struct student* students)` that populates the `id` and `score` fields of the array of 10 students passed as an argument.  Each student should have an `id` that corresponds to their index in the array (i.e. the first student in the array should have `id` 0). If each student's `id` is `x`, the student's score should be `(10 * x) % 50`.

3. Write a function `void output(struct student* students)` that prints the ids and scores of all 10 students.

4. Write a function `float avg(struct student* students)` that computes the average of all scores.

5. Write a function `int min(struct student* students)` that computes the minimum of all scores.

6. Write a function `void deallocate(struct student* stud)` that frees the memory allocated to students. Check that students is not `NULL` (`NULL == 0`) before you attempt to free it.

7. Write a function `void sort(struct student* stud)` that sorts students by descending score (i.e. highest scores at the top). You must sort the array *in-place* - that is, you should not allocate any additional memory.  *You may not use C sorting routines like `qsort()`.  You must implement the sort yourself.*

## Guidelines

*Deviation from the following guidelines will result in a zero score.*

* Do not change the function signatures (i.e. `void fooB(int k)`).
* Do not add or remove files. 

If you have any questions regarding the assignment, please use [the course Piazza](https://piazza.com/oregonstate/fall2016/cs261/home).

We will be using a test harness that calls your functions individually, but we will not call `main()`.  We will also examine your source code.  You are responsible for making sure each function operates as specified by using main to test them.

In general:

* A solution that does not compile is worse than...
* ... a solution that seg faults or otherwise crashes. This is worse than...
* ... a solution with the incorrect solution.

## Grading criteria

Your assignment will be graded by compiling it on `flip.engr.oregonstate.edu` using the provided `Makefile`, so make sure you have tested your work under those conditions.

The assignment is worth 100 points total.

* `Q0.c`: 25 points
  * 5 points: compiles
  * 8 points: `fooA()` works as specified
  * 8 points: `fooB()` works as specified
  * 4 points: `main()` does what is specified
* `Q1.c`: 75 points
  * 5 points: compiles
  * 10 points: `allocate()` behaves as specified, using `malloc()` to allocate an array with the correct number of students
  * 10 points: `generate()` behaves as specified, assigning the correct ID and score to each student
  * 10 points: `output()` behaves as specified, correctly printing the IDs and scores of the students
  * 10 points: `avg()` behaves as specified, correctly computing the average of all the scores
  * 10 points: `min()` behaves as specified, correctly computing the minimum of all the scores
  * 10 points: `deallocate()` behaves as specified, correctly freeing the memory allocated to the passed array after making sure the pointer is not `NULL`
  * 10 points: `sort()` behaves as specified, correctly sorting the students by descending score without using C sorting routines like `qsort()`

## Submission

We'll be using GitHub Classroom for this assignment.  You will submit your assignment via GitHub.  Just make sure your completed files are committed and pushed by the assignment's deadline to the `master` branch of the GitHub repo that was created for you by GitHub Classroom.
