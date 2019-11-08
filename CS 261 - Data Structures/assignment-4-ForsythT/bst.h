/*
  File: bst.h
  Interface definition of the binary search tree data structure.
*/

#ifndef __BST_H
#define __BST_H

#include "cirListDeque.h"
#include "structs.h"

/* Defines the type to be stored in the data structure.  These macros
 * are for convenience to avoid having to search and replace/dup code
 * when you want to build a structure of doubles as opposed to ints
 * for example.
 */

# ifndef BST_DATA_TYPE
# define BST_DATA_TYPE      struct data*
# endif

/* function used to compare two BST_DATA_TYPE values to each other, define this in your compare.c file */
int compare(BST_DATA_TYPE left, BST_DATA_TYPE right);
/* function used to print BST_DATA_TYPE values, define this in your compare.c file */
void print_type(BST_DATA_TYPE curval);


struct Node {
  BST_DATA_TYPE val;
  struct Node *left;
  struct Node *right;
};

struct BSTree {
  struct Node *root;

};

/* Declared in the c source file to hide the structure members from the user. */

/* Initialize binary search tree structure. */
void initBSTree(struct BSTree *tree);

/* Alocate and initialize search tree structure. */
struct BSTree *newBSTree();

/* Deallocate nodes in BST. */
void clearBSTree(struct BSTree *tree);

/* Deallocate nodes in BST and deallocate the BST structure. */
void deleteBSTree(struct BSTree *tree);

/*-- BST Bag interface --*/
int  isEmptyBSTree(struct BSTree *tree);
int     sizeBSTree(struct BSTree *tree);

void     addBSTree(struct BSTree *tree, BST_DATA_TYPE val);
int containsBSTree(struct BSTree *tree, BST_DATA_TYPE val);
void  removeBSTree(struct BSTree *tree, BST_DATA_TYPE val);
void printTree(struct BSTree *tree);

struct data * findNode(struct Node *tree, int val);
int countNodes(struct Node *tree);
int secondLargestNode(struct Node *tree);
void  flattenPreorder(struct Node *tree, struct cirListDeque * d);
void  flattenPostorder(struct Node *tree, struct cirListDeque * d);
void  flattenInorder(struct Node *tree, struct cirListDeque * d);


# endif
