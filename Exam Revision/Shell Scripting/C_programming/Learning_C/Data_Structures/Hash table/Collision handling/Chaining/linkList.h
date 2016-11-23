/*
	Author: Matthew Ta
	Date: 7/06/2015
	Description: Header file containing functions to use with the linked lists
*/
	
typedef struct _node *nodePtr;
typedef struct _list *List;

typedef char * Item;

// create a list 
List createList(void);

// delete a list
void deleteList(List);

// function prototypes
void addNode(List, Item);
void insertNode(List, Item, Item);
int deleteNode(List, Item);

// find the length of the linked list
int getLength(List);

// finds the number of times a specific value occurs in a list
Item *findNode(List l, Item value);

// print the list
void printList(List);

// remove duplicates
void removeDups(List l);

// copies nodes from src to des
void copyList(List src, List des);

// copies the list into an array
Item *copyListArray(List l); 

