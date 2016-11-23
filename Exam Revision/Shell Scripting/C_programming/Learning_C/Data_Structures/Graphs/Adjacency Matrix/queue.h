/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Interface functions for a queue ADT
*/

typedef struct _queueRep *Queue;

Queue newQueue(void); // create a new queue

void deleteQueue(Queue q); // delete a queue

void enQueue(Queue q, int item); // insert an item at the tail of q

int deQueue(Queue q); // remove an item from the head of the queue

void showQueue(Queue q); // shows the contents of the queue

int isEmptyQueue(Queue q); // determines if the queue is empty, returns 1 if empty and 0 otherwise


