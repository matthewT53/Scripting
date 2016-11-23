/*
	Name: Matthew Ta
	Date: 29/9/2015
	Description: Implementation of the priority queue ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "priorityQueue.h"

#define TRUE 1
#define FALSE 0

typedef struct _node *Node;

typedef struct _priorityQueue{
	Node head; // ptr to node with highest priority
	Node tail; // ptr to the other nodes in the queue
} priorityQueue;

typedef struct _node{
	Item data;
	int p; // priority
	Node next;
} node;

static Node newNode(Item vertex, int p); // function to create a new node
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
void joinPQueue(PQueue q, Item vertex, int p)
{
	Node n = newNode(vertex, p);
	
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
		free(temp);
	}

	return value;
}

/*
	Notes:
	* Updates a single node and reorders the PQueue
	* O(n)
	* could just simply swap the values.
*/
void reorder(PQueue q, Item vertex, int distance)
{
	Node cur = q->head;
	Node pNode = NULL; // prioritised node
	int largestP = 0; // highest priority

	int updateNode(PQueue q, Item vertex, int newPriority); // updates a node with a new priority
	void swapNodes(PQueue q, Node n1, Node n2);

	if (vertex != NO_UPDATE && distance != NO_UPDATE){ // only update if the user wants to update
		if (!updateNode(q, vertex, distance)) { printf("Coulnd't find vertex in queue.\n"); } // update a vertex with a new priority queue
	}

	if (cur != NULL){
		while (cur != NULL){
			if (cur->p > largestP){
				pNode = cur;
				largestP = cur->p;
			}
			cur = cur->next;
		}

		if (pNode != q->head && pNode != NULL){
			swapNodes(q, q->head, pNode);
		}
	}
}

int updateNode(PQueue q, Item vertex, int newPriority)
{
	int foundVertex = FALSE;
	Node cur = q->head;
	while (cur != NULL){
		if (cur->data == vertex){
			cur->p = newPriority;
			foundVertex = TRUE;
		}
		cur = cur->next;
	}
	return foundVertex;
}

void showPQueue(PQueue q)
{
	Node cur = q->head;
	while (cur != NULL){
		printf("[Data: %d Pri: %d]->", cur->data, cur->p);
		cur = cur->next;
	}
	printf("[X]\n");
}

/*
	* Swaps two nodes
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
			beforeN1->next = n2;
			n2->next = afterN1;

			beforeN2->next = n1;
			n1->next = afterN2;
		}
	}
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

static Node newNode(Item vertex, int p)
{
	Node n = malloc(sizeof(node));
	assert(n != NULL);
	n->data = vertex;
	n->p = p;
	n->next = NULL;
	return n;
}
