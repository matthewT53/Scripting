/*
	Name: Matthew Ta
	Date: 29/9/2015
	Description: Implementation of the priority queue ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "priorityQueue.h"

typedef struct _node *Node;

typedef struct _priorityQueue{
	Node head; // ptr to node with highest priority
	Node tail; // ptr to the other nodes in the queue
} priorityQueue;

typedef struct _node{
	Item data;
	int priority;
	Node next;
} node;

static Node newNode(Item data); // function to create a new node
static void findPrevAndNext(PQueue q, Node n, Node *prevN, Node *nextN); // helper function

PQueue newPQueue(void)
{
	PQueue q = malloc(sizeof(priorityQueue));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void deletePQueue(PQueue q)
{
	Node cur, temp;
	cur = q->head;
	while (cur != NULL){
		temp = cur;
		cur = cur->next;
		free(temp);
	}

	free(q);
}

// insert at the head
void joinPQueue(PQueue q, Item data, int p)
{
	Node n = newNode(data);
	n->priority = p;

	if (q->head == NULL && q->tail == NULL){ // queue is empty
		q->head = n;
	}

	else{ // queue is not empty
		q->tail->next = n;
	}

	q->tail = n;
}

// remove from the head
Item leavePQueue(PQueue q)
{
	Node temp;
	Item value = 0;
	if (q->head != NULL){
		temp = q->head;
		value = temp->data;
		q->head = q->head->next;
		if (q->head == NULL){ // item after head is null therefore tail should also be null
			q->tail = NULL;
		}
		free(temp);
	}

	return value;
}

/*
	Notes:
	* node with the highest value with be highest priority
	* O(n)
	* could just simply swap the values. Although if the values take up too much memory it is more efficient to simply swap nodes
	  since this simply involves swapping pointers which are a couple of bytes in size.
*/
void reorder(PQueue q, Item vertex, int distance)
{
	Node cur = q->head;
	Node smallestNode = NULL;
	Item smallestValue = INF;

	void swapNodes(PQueue q, Node n1, Node n2);

	if (vertex != NO_UPDATE && distance != NO_UPDATE){
		if (!updatePQueue(q, vertex, distance)) { printf("Something went wrong.\n"); }
	}

	if (cur != NULL){
		while (cur != NULL){
			if (cur->priority < smallestValue){
				smallestNode = cur;
				smallestValue = cur->priority;
			}
			cur = cur->next;
		}

		if (smallestNode != q->head && smallestNode != NULL){
			swapNodes(q, q->head, smallestNode);
		}
	}
}

int updatePQueue(PQueue q, Item v, int p)
{
	Node cur = q->head;
	int returnValue = FALSE;
	while (cur != NULL){
		if (cur->data == v){
			cur->priority = p;
			returnValue = TRUE;
			break;
		}
		cur = cur->next;
	}

	return returnValue;
}

void showPQueue(PQueue q)
{
	Node cur = q->head;
	while (cur != NULL){
		printf("[%d Priority = %d]->", cur->data, cur->priority);
		cur = cur->next;
	}
	printf("[X]\n");
}

/*
	* Swaps two nodes
	* Fails when the two nodes are next to each other
	* Swapping nodes is only feasible when data of each node is extremely large
	* the code below can possibly be made more efficient
	* O(n) time complexity
*/
void swapNodes(PQueue q, Node n1, Node n2)
{
	Node beforeN1 = NULL, afterN1 = NULL;
	Node beforeN2 = NULL, afterN2 = NULL;
	
	if (q->head != NULL && n1 != n2){ // account for empty list
		// find nodes before and after n1
		findPrevAndNext(q, n1, &beforeN1, &afterN1);
		findPrevAndNext(q, n2, &beforeN2, &afterN2);

		// swap the nodes
		if (beforeN1 == NULL){ // case where n1 is the first node (head)
			// printf("Path 1.\n");
			q->head = n2;
			if (n1->next == n2){ // detect if n1 and n2 are neighbours
				q->head->next = n1;
			}

			else{
				q->head->next = afterN1;
				beforeN2->next = n1;
			}
			n1->next = afterN2;
		}

		else if (beforeN2 == NULL){ // when n2 is the first node
			// printf("Path 2.\n");
			q->head = n1;
			if (n2->next == n1){ // n2 is first node and neightbours with n2
				q->head->next = n2;
			}

			else{
				q->head->next = afterN2;
				beforeN1->next = n2;
			}

			n2->next = afterN1;
		}

		else{ // swap n1 and n2
			// printf("Path 3.\n");
			beforeN1->next = n2;
			n2->next = afterN1;

			beforeN2->next = n1;
			n1->next = afterN2;
		}
	}
}

int isEmptyPQ(PQueue q)
{
	return (q->head == NULL && q->tail == NULL);
}

static void findPrevAndNext(PQueue q, Node n, Node *prevN, Node *nextN)
{
	Node cur = q->head; 
	Node prev = NULL;

	while (cur != NULL){
		if (cur == n){
			*prevN = prev;
			*nextN = cur->next;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}

static Node newNode(Item data)
{
	Node n = malloc(sizeof(node));
	assert(n != NULL);
	n->data = data;
	n->next = NULL;
	return n;
}
