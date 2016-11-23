/*
	Name: Matthew Ta
	Date: 7/6/2015
	Description: Implementation of the interface functions for the link list ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkList.h"

typedef struct _node{
	int value;
	nodePtr next;
} node;

typedef struct _list{
	nodePtr head;
} list;


List createList(void){
	List newList = malloc(sizeof(list));
	newList->head = NULL;
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

void addNode(List l, int valueToAdd){
	nodePtr currentNode, lastNode, newNode;
	currentNode = l->head;
	newNode = malloc(sizeof(node));
	
	// what if the list is empty?
	if (l->head == NULL){
		l->head = newNode;
		lastNode = l->head;
		lastNode->value = valueToAdd;
		lastNode->next = NULL;
	}
	
	else{
		// get the pointer to the last node
		while (currentNode != NULL){
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
		
		lastNode->next = newNode;
		newNode->value = valueToAdd;
		newNode->next = currentNode;
	}
}

void printList(List l){
	nodePtr currentNode;
	currentNode = l->head;	
		
	// loop through the list and print out the nodes
	while (currentNode != NULL){
		printf("[%d]->", currentNode->value);
		currentNode = currentNode->next;
		
	}
	
	// print the null node
	printf("[X].\n");
}

int getLength(List l){
	int length = 0;
	nodePtr currentNode;
	
	currentNode = l->head;
	// loop through the list and count the number of nodes
	while (currentNode != NULL){
		length++;
		currentNode = currentNode->next;
	}

	return length;
}

int findNode(List l, int value)
{
	int occurences = 0;
	nodePtr currentNode;
		
	for ( currentNode = l->head; currentNode != NULL; currentNode = currentNode->next ){
		if (currentNode->value == value){
			occurences++;
		}
	}

	return occurences;
}

void deleteNode(List l, int value)
{
	nodePtr cur = NULL, prev = NULL;
	cur = l->head;
	if (cur != NULL){
		// might be first node
		if (cur->value == value){
			l->head = cur->next;
			free(cur);
		}

		else{
			while (cur != NULL){
				if (cur->value == value){
					prev->next = cur->next;
					free(cur);
					break;
				}

				prev = cur;
				cur = cur->next;
			}
		}

	}

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
				if ( cur->value == searchn->value ){ // delete the duplicate
					temp = searchn;
					prev->next = searchn->next;
					searchn = prev;
					free(temp);
				}			

				prev = searchn;	
				searchn = searchn->next;
			}
	
			cur = cur->next;
		}
	}

}

void copyListArray(int *array, List l, const int size)
{
	int i;
	nodePtr cur;
	
	for ( i = 0, cur = l->head; i < size && cur != NULL; i++, cur = cur->next){
		array[i] = cur->value;
	}
}

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




