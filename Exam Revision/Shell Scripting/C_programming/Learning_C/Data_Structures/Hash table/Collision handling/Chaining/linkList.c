/*
	Name: Matthew Ta
	Date: 7/6/2015
	Description: Implementation of the interface functions for the link list ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkList.h"

// boolean constants
#define TRUE 1
#define FALSE 0

typedef struct _node{
	Item value;
	nodePtr next;
} node;

typedef struct _list{
	nodePtr head;
	int length; // # nodes in the list
} list;

static nodePtr newNode(Item it); // creates a new node

List createList(void){
	List newList = malloc(sizeof(list));
	newList->head = NULL;
	newList->length = 0;
	return newList;
}

void deleteList(List l){
	nodePtr currentNode, previousNode;
	
	currentNode = l->head;
	if (currentNode != NULL){
		while (currentNode != NULL){
			previousNode = currentNode;
			currentNode = currentNode->next;
			free(previousNode);
		}

		l->head = NULL;
	}
	
	// list is already empty
	else{
		l->head = NULL;
	}
}

void addNode(List l, Item it)
{
	nodePtr cur = NULL;
	if (l != NULL){
		if (l->head == NULL){
			l->head = newNode(it);
		}

		else{
			cur = l->head;
			while(cur->next != NULL){
				cur = cur->next;
			}

			cur->next = newNode(it);
		}
		l->length++;
	}	
}

// creates a new node
static nodePtr newNode(Item it)
{
	nodePtr n = malloc(sizeof(node));
	assert(n != NULL && it != NULL);
	n->value = it;
	n->next = NULL;
	return n;
}

void printList(List l){
	nodePtr currentNode;
	currentNode = l->head;	
		
	// loop through the list and print out the nodes
	while (currentNode != NULL){
		printf("[%s]->", currentNode->value);
		currentNode = currentNode->next;
		
	}
	
	// print the null node
	printf("[X].\n");
}

int getLength(List l){
	int length = 0;
	if (l != NULL){
		length = l->length;
	}
	return length;
}

Item *findNode(List l, Item value)
{
	Item *it = NULL;
	nodePtr currentNode;
		
	for ( currentNode = l->head; currentNode != NULL; currentNode = currentNode->next ){
		if (strcmp(currentNode->value, value) == 0){
			it = &currentNode->value;
			break;
		}
	}
	return it;
}

int deleteNode(List l, Item value)
{
	int deleted = FALSE;
	nodePtr cur = NULL, prev = NULL;
	if (l != NULL){
		cur = l->head;
		// might be first node
		if (cur != NULL){
			if ( strcmp(cur->value, value) == 0 ){
				l->head = cur->next;
				if (cur->value != NULL) { l->length--; free(cur->value); cur->value = NULL; }
				free(cur);
				deleted = TRUE;
			}

			else{
				while (cur != NULL){
					if (strcmp(value, cur->value) == 0){
						prev->next = cur->next;
						if (cur->value != NULL) { l->length--; free(cur->value); cur->value = NULL; }
						free(cur);
						deleted = TRUE;
						break;
					}
					prev = cur;
					cur = cur->next;
				}
			}
		}
	}
	return deleted;
}

void removeDups(List l)
{
	nodePtr cur = NULL, temp = NULL, searchn = NULL, prev = NULL;

	/*
		Cases:
		* 2 nodes in list same value
		* remove last node
		* remove middle of list
		* 2 consec dups
	*/
	
	if ( l != NULL ){
		cur = l->head;
		while ( cur != NULL ){
			searchn = cur->next;
			prev = cur;
			while ( searchn != NULL ){
				if ( strcmp(cur->value, searchn->value) == 0 ){ // delete the duplicate
					temp = searchn;
					prev->next = searchn->next;
					searchn = prev;
					free(temp->value);
					free(temp);
				}			

				prev = searchn;	
				searchn = searchn->next;
			}
	
			cur = cur->next;
		}
	}

}

// copies a list into another list
void copyList(List src, List des)
{
	nodePtr cur = src->head;
	if (cur == NULL) return;
	else{
		while (cur != NULL){
			addNode(des, cur->value);
			cur = cur->next;
		}
	}
}

// copies a list into an array
Item *copyListArray(List l)
{
	int i = 0;
	Item *its = NULL;
	nodePtr cur = NULL;
	if (l != NULL && l->head != NULL){
		its = malloc(sizeof(Item) * l->length);
		assert(its != NULL);
		cur = l->head;
		while (cur != NULL){
			its[i] = cur->value;
			cur = cur->next;
			i++;
		}
	}
	return its;
}

