/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Implementation of a Queue ADT
*/

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct _queueRep{
    Node head;
    Node tail;
} queueRep;

typedef struct _node{
    Link value;
    Node next;
} node;

// create a new queue
Queue newQueue(void)
{
    Queue q = malloc(sizeof(queueRep));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// add a node to the tail of the queue
void enQueue(Queue q, Link value)
{
    Node newNode(Link v);
    Node n = newNode(value);

    if (n != NULL){
        // check if empty queue
        if (q->head == NULL){
            q->head = n;
        }

        else{
            // add to the tail
            q->tail->next = n;
        }
        q->tail = n;
    }

    else{
        printf("Unable to add item to queue.\n");
    }
}

Link deQueue(Queue q)
{
    Node temp;
    Link value = NULL;

    if (q->head != NULL){
        temp = q->head;
        value = temp->value;
        q->head = q->head->next;
        if (q->head == NULL){ // list is empty
            q->tail = NULL;
        }
        free(temp);
    }

    return value;
}

Node newNode(Link v)
{
    Node n = malloc(sizeof(node));
    if (n != NULL){
        n->value = v;
        n->next = NULL;
    }
    return n;
}

void showQueue(Queue q)
{   
    Node curr = q->head;
    while (curr != NULL){
        printf("[%p]->", curr->value);
        curr = curr->next;
    }
    printf("[X]\n");
}

void deleteQueue(Queue q)
{
    Node curr = q->head;
    Node temp;

    while (curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp);        
    }

    free(q);
}

int emptyQueue(Queue q)
{
	return (q->head == NULL && q->tail == NULL);
}
