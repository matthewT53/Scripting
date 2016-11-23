/*
	Author: Matthew Ta
	Date: 7/06/2015
	Description: Header file containing functions to use with the linked lists
*/
	
typedef struct _node *nodePtr;
typedef struct _list *List;

// move these struct into the header file to run the test file
typedef struct _node{
	int value;
	nodePtr next;
} node;

typedef struct _list{
	nodePtr head;
} list;


// create a list 
List createList(void);

// delete a list
void deleteList(List);

// function prototypes
void addNode(List, int);
void insertNode(List, int, int);
void deleteNode(List, int);

// find the length of the linked list
int getLength(List);

// sorting functions, these functions can be applied white the
// nodePtr is being added into the list
void sortAscending(List);
void sortDescending(List);

// finds the number of times a specific value occurs in a list
int findNode(List l, int value);

// remove duplicates
void removeDups(List l);

// copy list into an array
void copyListArray(int *array, List l, const int size);

// print the list
void printList(List);

// frontBackSplit
void frontBackSplit(List, List, List);

// moveNode moves the first node from List2 to the frotn of List1
void moveNode(List, List);

// alternating split (source list is unchanged)
void alternatingSplit(List, List, List);

// alternating split 2 where sourcelist is changed and each is placed into the sublist in reverse order
void alternatingSplit2(List, List, List);

// shuffle merge
List shuffleMerge(List, List);

// sorted merge
List sortedMerge(List, List);

/* both pointers are the current node in a list, this function copies the node from the second node pointer to the list of the of the first pointer.*/
void copyNodes(nodePtr *, nodePtr *, int *);

// merge sort
void mergeSort(List *);

// reverse a list
void reverse(List);


