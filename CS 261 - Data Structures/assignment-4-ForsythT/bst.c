/*
   File: bst.c
    Implementation of the binary search tree data structure.

*/
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "bst.h"



/*
   function to initialize the binary search tree.
    param tree
     pre: tree is not null
     post:tree size is 0
     root is null
*/
void initBSTree(struct BSTree *tree)
{

  tree->root = 0;
}

/*
    function to create a binary search tree.
      param: none
        pre: none
	  post: tree->count = 0
	  tree->root = 0;
*/


struct BSTree*  newBSTree()
{
  struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
  assert(tree != 0);

  initBSTree(tree);
  return tree;
}

/*----------------------------------------------------------------------------*/
/*
  function to free the nodes of a binary search tree
  param: node  the root node of the tree to be freed
   pre: none
    post: node and all descendants are deallocated
*/
void _freeBST(struct Node *node)
{
  if (node != 0) {
    _freeBST(node->left);
    _freeBST(node->right);
    free(node);
  }
}

/*
   function to clear the nodes of a binary search tree
    param: tree    a binary search tree
     pre: tree ! = null
      post: the nodes of the tree are deallocated
      tree->root = 0;
      tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
  _freeBST(tree->root);
  tree->root = 0;

}

/*
   function to deallocate a dynamically allocated binary search tree
    param: tree   the binary search tree
     pre: tree != null;
      post: all nodes and the tree structure itself are deallocated.
*/

void deleteBSTree(struct BSTree *tree)
{
  clearBSTree(tree);
  free(tree);
}


/*----------------------------------------------------------------------------*/
/*
   function to determine if  a binary search tree is empty.

    param: tree    the binary search tree
     pre:  tree is not null
*/
int isEmptyBSTree(struct BSTree *tree) { return tree == 0; }



/*----------------------------------------------------------------------------*/
/*
   recursive helper function to add a node to the binary search tree.
    HINT: You have to use the compare() function to compare values.
    param:  curthe current root node
    valthe value to be added to the binary search tree
    pre:val is not null
*/
struct Node *_addNode(struct Node *cur, BST_DATA_TYPE val)
{

  struct Node *newnode;
  /* case1 - cur is null */
  if (cur == NULL)
    {/*create new node and return*/
      newnode = (struct Node *)malloc(sizeof(struct Node));
      assert(newnode != 0);
      newnode->val = val;
      newnode->left = newnode->right = 0;
      return newnode;
    }
  if (compare(val,cur->val) == -1)
    cur->left = _addNode(cur->left,val);
  else if (compare(val, cur->val) == 1)
    cur->right = _addNode(cur->right, val);
  return cur;
}

/*
   function to add a value to the binary search tree
    param: tree   the binary search tree
    valthe value to be added to the tree

    pre:tree is not null
    val is not null
     pose:  tree size increased by 1
     tree now contains the value, val
*/

void addBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{
  tree->root = _addNode(tree->root, val);

}

/*
   function to determine if the binary search tree contains a particular element
    HINT: You have to use the compare() function to compare values.
    param:treethe binary search tree
    valthe value to search for in the tree
    pre:tree is not null
    val is not null
    post:none
*/


int containsBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{

  	struct Node *cur = tree->root;

  	while (cur != 0) {
    		if (compare(val,cur->val) == 0)
      			return 1; /* Return true if val found. */
    		if (compare(val, cur->val) == -1)
      			cur = cur->left; /* Otherwise, go to the left */
    		else 
			cur = cur->right; /* or right, depending on val. */
  	}
  	return 0;


}

/*
    helper function to find the left most child of a node
      return the value of the left most child of cur
      param: curthe current node
      pre:cur is not null
        post: none
*/
BST_DATA_TYPE _leftMost(struct Node *cur)
{

  	while (cur->left != 0)
  		cur = cur->left;
  	return cur->val;

}

/*
    recursive helper function to remove the left most child of a node
      HINT: this function returns cur if its left child is NOT NULL. Otherwise,
        it returns the right child of cur and free cur.

	 Note:  If you do this iteratively, the above hint does not apply.

	 param: curthe current node
	 pre:cur is not null
	 post:the left most node of cur is not in the tree
*/
struct Node *_removeLeftMost(struct Node *cur)
{


  	struct Node *node;

  	if (cur->left != 0) {
    		cur->left = _removeLeftMost(cur->left);
    		return cur;
  	}

  	node = cur->right;
  	free(cur);
  	return node;
}

/*
    recursive helper function to remove a node from the tree
      HINT: You have to use the compare() function to compare values.
      param:curthe current node
      valthe value to be removed from the tree
      pre:val is in the tree
      cur is not null
      val is not null
*/
struct Node *_removeNode(struct Node *cur, BST_DATA_TYPE val)
{

  	struct Node *temp;
  	if (compare(val, cur->val) == 0) { /* Found val. */
    		if (cur->right == 0) {
      			temp = cur->left;
      			free(cur);
      			return temp;
    		}
    		cur->val = _leftMost(cur->right);
    		cur->right = _removeLeftMost(cur->right);
  	}
  	else if (compare(val, cur->val) == -1)
    		cur->left = _removeNode(cur->left, val);
  	else
    		cur->right = _removeNode(cur->right,val);
  	return cur;
}
/*
    function to remove a value from the binary search tree
      param: tree   the binary search tree
      valthe value to be removed from the tree
      pre:tree is not null
      val is not null
      val is in the tree
      pose:tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{
  	if (containsBSTree(tree, val)) {
    		tree->root = _removeNode(tree->root, val);
  	}
}

struct data * findNode(struct Node *tree, int val){
  /*
   Finds a data struct with "number" equal to val and returns it. If
  the node is not found, return NULL
   
   Your code should take advantage of the BST property to 
      traverse only the necessary tree nodes
  */
	if(tree == NULL) //not found
		return NULL;
	else if(tree->val->number == val) //end case
		return tree->val;
	else if(tree->val->number < val) //go the right if val is bigger
		return findNode(tree->right, val);
	else //val has to be smaller if not greater or equal to, so go left
		return findNode(tree->left, val);
	return NULL;
}

int countNodes(struct Node *tree){
  /*  Returns the number of nodes present in tree including tree
 */
	int count = 1; //gotta count the root
	if(tree != NULL){
		if(tree->left != NULL)
			count += countNodes(tree->left); //count the left tree
		if(tree->right != NULL)
			count += countNodes(tree->right); //count the right tree
		return count;
	}
	return 0;
}

int secondLargestNode(struct Node *tree){
  /*
    Given a tree containing struct data values with "number" greater
     than zero, returns the second largest "number" found in tree or
     its children.  If tree contains less than two nodes return -1;
  */
	struct Node *cur;
	if(tree == NULL || (tree->left == NULL && tree->right == NULL)) //tree is empty or only 1 node in tree
  		return -1; //return false
	else if(tree->right == NULL && tree->left != NULL){
		cur = tree->left; 
		while(cur->right != NULL){ //navigate to right most node of the left child of root
			cur = cur->right;
		}
		return cur->val->number; //return node
	}
	else{ //doesn't matter if there are nodes less than root as long as there are some greater than, so this covers both (tree->right != NULL && tree->left != NULL) and (tree->right != NULL && tree->left == NULL)
		cur = tree;
		while(cur->right->right != NULL){ //navigate to node just before right most node of tree
			cur = cur->right;
		}
		return cur->val->number; //return node
	}
}

void  flattenPreorder(struct Node *tree, struct cirListDeque * d){
  /* Performs a preorder traversal of tree and appends nodes in the
     order of the traversal to the deque. The first call to
     flattenPreorder should pass the root node of the bst as tree
     and cirListDeque should be a new, empty deque */
	//preorder A L R
	if(tree != NULL){
		addBackCirListDeque(d, tree->val);
		flattenPreorder(tree->left, d);
		flattenPreorder(tree->right, d);	
	}
  	return;
}
void  flattenPostorder(struct Node *tree,struct cirListDeque * d){
  /* Performs a postorder traversal of tree and appends nodes in the
     order of the traversal to the deque. The first call to
     flattenPreorder should pass the root node of the bst as tree
     and cirListDeque should be a new, empty deque */
	//postorder L R A
	if(tree != NULL){
		flattenPostorder(tree->left, d);
		flattenPostorder(tree->right, d);
		addBackCirListDeque(d, tree->val);
	}
  	return;
}
void  flattenInorder(struct Node *tree,struct cirListDeque * d){
  /* Performs a inorder traversal of tree and appends nodes in the
     order of the traversal to the deque. The first call to
     flattenPreorder should pass the root node of the bst as tree
     and cirListDeque should be a new, empty deque */
	//inorder L A R
	if(tree != NULL){
		flattenInorder(tree->left, d);
		addBackCirListDeque(d, tree->val);
		flattenInorder(tree->right, d);
	}
  	return;
}
/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used
   in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
  if (cur == 0) return;
  printf("(");
  printNode(cur->left);
  /*Call print_type which prints the value of the BST_DATA_TYPE*/
  print_type(cur->val);
  printNode(cur->right);
  printf(")");
}

void printTree(struct BSTree *tree) {
  if (tree == 0) return;
  printNode(tree->root);
}
/*----------------------------------------------------------------------------*/

#endif
