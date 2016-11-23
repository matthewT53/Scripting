/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Interface functions for a queue ADT
*/

typedef struct _queueRep *Queue;
typedef struct _node *Node;

Queue newQueue(void); // create a new queue

void deleteQueue(Queue q); // delete a queue

void enQueue(Queue q, int item); // insert an item at the tail of q

int deQueue(Queue q); // remvoe an item from the head of the queue

void showQueue(Queue q);


