/*
    Name: Matthew Ta
    Date:
    Description: Implementation of the double linked list
*/

#include <stdio.h>
#include <stdlib.h>

#include "Dll.h"

static Node createNode(const int value);

typedef struct _DllRep{
    Node head; // head of the list
    Node curr; // current node 
    Node tail; // last node in list
	int numNodes; // keeps track of the number of nodes in the list
} DllRep;

typedef struct _node{
    int value;
    Node prev;
    Node next;
} node;

List createList(void)
{
    List newList = (List) malloc(sizeof(DllRep));
    newList->head = NULL;
    newList->curr = NULL;
    newList->tail = NULL;
    return newList;
}

void deleteList(List l)
{
	Node n = l->head, temp = NULL;

    while (n != NULL){
		temp = n;
		n = n->next;
		free(temp);
	}
    free(l);
}

// inserts after the current node
void insertNode(List l, int item)
{
	Node n = createNode(item);	
	if (l->head == NULL){ // empty list
		l->head = n;
		l->curr = n;
		l->tail = n;
	}

	else if (l->head == l->tail){ // list contains one node
		l->curr->next = n;
		n->prev = l->curr;
		n->next = NULL;
		l->tail = n;
	}

	else{
		n->next = l->curr->next; // n points to node after cur
		l->curr->next->prev = n;
		n->prev = l->curr;
		l->curr->next = n; // curr now points to n
		if (n->next == NULL){ // check if inserted at end of list
			l->tail = n;
		}
		l->curr = n;
	}
	l->numNodes++;
}

static Node createNode(const int value)
{
	Node newNode = malloc(sizeof(node));
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;	
}

void removeNode(List l, int item)
{
	Node cur = l->head;
	
	while (cur != NULL){
		if (cur->value == item){
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			l->numNodes--;
			free(cur);
			break;
		}
		cur = cur->next;
	}
}

void showList(List l)
{
	Node cur = l->head;

	printf("# nodes = %d.\n", l->numNodes);
	printf("l->head: %p, l->curr: %p and l->tail: %p\n", l->head, l->curr, l->tail);

	while (cur != NULL){
		printf("[%d]<->", cur->value);
		cur = cur->next;
	}
	printf("[X]\n");
}



