/* 	dynArr.h : Dynamic Array implementation. */
#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1

/*  RAM: All this type stuff This should go elsewhere! */

# define KT void *
# define VT void *


#define TYPE      char  //int
#define TYPE_SIZE sizeof(char)
#define LT(A, B) ((A) < (B))
#define EQ(A, B) ((A) == (B))

#define PRINT_STR "%df"
#define CAST_STR char *


/* function used to compare two TYPE values to each other */
int compare(TYPE left, TYPE right);
typedef int (*comparator)(void *left, void*right);

typedef struct DynArr DynArr;

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

struct DynArrIter;


/* Dynamic Array Functions */
DynArr *createDynArr(int cap);
void deleteDynArr(DynArr *v);

int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);

/* Stack interface. */
int isEmptyDynArr(DynArr *v);
void pushDynArr(DynArr *v, TYPE val);
TYPE topDynArr(DynArr *v);
void popDynArr(DynArr *v);

/* Bag Interface */
int containsDynArr(DynArr *v, TYPE val);
void removeDynArr(DynArr *v, TYPE val);

/* Heap-based Priority Queue Interface */
TYPE getMinHeap(DynArr *heap);
void addHeap(DynArr *heap, TYPE node, comparator compare);
void removeMinHeap(DynArr *heap);
void sortHeap(DynArr *heap, comparator compare);

/* Iterator Interface */
struct DynArrIter *createDynArrIter(struct DynArr *da);
void  initDynArrIter (struct DynArr *da, struct DynArrIter *itr);
int hasNextDynArrIter (struct DynArrIter *itr);
TYPE nextDynArrIter (struct DynArrIter *itr);
void removeDynArrIter (struct DynArrIter *itr);


/* Utility function*/
void copyDynArr(DynArr *source, DynArr *destination);
void printDynArr(DynArr *v);
#endif
