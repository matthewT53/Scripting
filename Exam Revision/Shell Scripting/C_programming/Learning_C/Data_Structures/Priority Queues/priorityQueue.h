/* 
	Name: Matthew Ta
	Date: 23/9/2015
	Description: Interface for a priority queue ADT
*/

#define NO_UPDATE -1

typedef struct _priorityQueue *PQueue;
typedef int Item;

PQueue newPQueue(void); // create a new priority queue
void deletePQueue(PQueue q); // free a priority queue

void joinPQueue(PQueue q, Item vertex, int p); // insert a value into the priority queue
Item leavePQueue(PQueue q); // remove value with highest priority from queue

void reorder(PQueue q, Item vertex, int distance); // updates the priority of a node and then updates the queue

void showPQueue(PQueue q); // show the contents of the queue

// predicate functions
int isEmptyPQ(PQueue q); // returns true if queue is empty
