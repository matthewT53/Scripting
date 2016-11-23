/*
	Author: Matthew Ta
	Date: 7/06/2015
	Description: Header file containing functions to use with the linked lists
*/
	
typedef struct _node *nodePtr;
typedef struct _list *List;

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

// finds the number of times a specific value occurs in a list
int findNode(List l, int value);

// print the list
void printList(List);

// remove duplicates
void removeDups(List l);

// copy list into an array
void copyListArray(int *array, List l, const int size);

// copy a list into another list
void copyList(List src, List des);
