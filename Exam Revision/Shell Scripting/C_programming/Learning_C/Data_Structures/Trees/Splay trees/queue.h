/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Interface functions for a queue ADT
*/

#include "splay.h"

typedef struct _queueRep *Queue;
typedef struct _node *Node;

Queue newQueue(void); // create a new queue

void deleteQueue(Queue q); // delete a queue

void enQueue(Queue q, Link item); // insert an item at the tail of q

Link deQueue(Queue q); // remvoe an item from the head of the queue

void showQueue(Queue q);

int emptyQueue(Queue q); // returns true if the queue is empty


