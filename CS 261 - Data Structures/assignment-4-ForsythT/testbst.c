#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "structs.h"
#include "cirListDeque.h"

int fails = 0;
int verbose = 1;
void assertTrue(int predicate, char *message) 
{

	if (!predicate){
	  printf("%s: ", message);
	  printf("FAILED\n");
	  fails++;
	}
	else if (verbose){
	  printf("%s: ", message);
	  printf("PASSED\n");
	  
	}
}



struct BSTree *createTestBST(int* array,int size) {

  struct BSTree *tree = malloc(sizeof(struct BSTree)); 
  initBSTree(tree);

  int i;

  for (i=0;i<size;i++){
    struct data *mydata = (struct data*) malloc(sizeof(struct data));
    mydata->number = array[i];
    mydata->name   = "---";
    addBSTree(tree, mydata);

  }

  return tree;

}

void findTest(struct BSTree* tree,int findit,int expected){

  struct data* d = findNode(tree->root,findit);
  char * tmp;
  if(d!=NULL){
    asprintf(&tmp,"findNode(%d),Found value:%d",findit,d->number);
    assertTrue(findit==d->number,tmp);
    assertTrue(expected,"Expected element to be found");
  }
  else{
    asprintf(&tmp,"Not found:%d",findit);
    assertTrue(!expected,"Expected element to be missing");

  }
  free(tmp);
}

int testBST(struct BSTree * tree){

  /*Print the entire tree*/
  printTree(tree);
  printf("\n");
  struct cirListDeque * cld = createCirListDeque();
  flattenPreorder(tree->root,cld);
  printf("Preorder:");
  printCirListDeque(cld);

  struct cirListDeque * cld2 = createCirListDeque();
  printf("Inorder:");
  flattenInorder(tree->root,cld2);
  printCirListDeque(cld2);

  struct cirListDeque * cld3 = createCirListDeque();
  printf("Postorder:");
  flattenPostorder(tree->root,cld3);
  printCirListDeque(cld3);

  printf("2nd Max:%d\n",secondLargestNode(tree->root));
  printf("Count:%d\n",countNodes(tree->root));


  deleteCirListDeque(cld);
  deleteCirListDeque(cld2);
  deleteCirListDeque(cld3);

  return 0;
}

int main(int argc, char *argv[])
{

  int in[] ={5,3,1,10};
  /*(( 1 ( 3 ) ) 5 ( 10 ))*/
  struct BSTree * b = createTestBST(in,4);
  testBST(b);
  findTest(b,1,1);
  findTest(b,4,0);
  findTest(b,5,1);
  findTest(b,10,1);

  deleteBSTree(b);


  int in2[] ={1,2,3,4,5};

  struct BSTree * b2 = createTestBST(in2,5);  
  findTest(b2,1,1);
  findTest(b2,4,1);
  findTest(b2,5,1);
  findTest(b2,10,0);

  testBST(b2);
  deleteBSTree(b2);

  int in3[] ={5,1,2,3,4};

  struct BSTree * b3 = createTestBST(in3,5);  
  findTest(b2,1,1);
  findTest(b2,4,1);
  findTest(b2,5,1);
  findTest(b2,10,0);

  testBST(b3);
  deleteBSTree(b3);



}

