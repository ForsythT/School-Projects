# Assignment 4

**Due 4:59pm on Monday, 10/31/2016**

The goal of this assignment is to start working with binary search trees.  Follow the instructions below, filling in and augmenting the appropriate places in the provided code, as requested.

In the files `bst.h` and `bst.c`, a binary search tree implementation is given. Note that the value of each BST node is a pointer to the following struct found in `structs.h`:

```
struct data {
	int number;
	char *name;
};
```

You are to complete the following functions in `bst.c`:

* `struct data * findNode(struct Node* tree, int val)`
* `int countNodes(struct Node* tree)`
* `int secondLargestNode(struct Node* tree)`
* `void flattenPreorder(struct Node* tree, struct cirListDeque* d)`
* `void flattenPostorder(struct Node* tree, struct cirListDeque* d)`
* `void flattenInorder(struct Node* tree, struct cirListDeque* d)`

A description for each function is provided in the comments of the `bst.c` file.

In the latter three functions, you can expect that `d` will be an initialized deque containing no items.  You are required to add `struct * data` pointers to the end of deque as you traverse the tree. For example, a BST `t`
```
         4
        / \
       1   8
          /
         5    
```
called with `flattenInorder(t,d)` (where `d` is an empty deque) would return with deque `d` containing `struct data*` pointers with the following `number` values in the order below:
```
1 <-> 4 <-> 5 <-> 8
```

The call `flattenPostorder(t,d)` would return with deque `d` containing `struct data*` pointers with the following `number` values in the order below:
```
1 <-> 5 <-> 8 <-> 4
```

You can test your code using `testbst.c`.

## Grading criteria

Your assignment will be graded by compiling it on `flip.engr.oregonstate.edu` using the provided `Makefile`, so make sure you have tested your work under those conditions.  If you currently don't have access to `flip`, you should be able to create an ENGR account at https://teach.engr.oregonstate.edu/ (follow the link that says "Create a new account").

Some other requirements:
* You may not change the function signatures (i.e. `void foo(int k)`).
* You may not add or remove files.

The assignment is worth 100 points total.

* 20 points: `findNode()`
* 10 points: `countNodes()`
* 10 points: `secondLargestNode()`
* 20 points: `flattenPreorder()`
* 20 points: `flattenPostorder()`
* 20 points: `flattenInorder()`

## Submission

We'll be using GitHub Classroom for this assignment. You will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at your assignment repo on the github.com (i.e. github.com/OSU-CS261-F16/assignment-4-YourGitHubUsername). If your changes show up there, you can consider your files submitted.
