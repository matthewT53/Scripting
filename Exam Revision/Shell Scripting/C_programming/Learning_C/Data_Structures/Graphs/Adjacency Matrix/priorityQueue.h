/* 
	Name: Matthew Ta
	Date: 23/9/2015
	Description: Interface for a priority queue ADT
*/

// constants for the shortest path
#define INF 1000 // the max distance can be > 100 since a->b->c->d can have a very high value
#define NO_UPDATE -1 // user specifies that do not want to update any nodes when reordering the queue

// boolean constants
#define TRUE 1
#define FALSE 0

typedef struct _priorityQueue *PQueue;
typedef int Item;

PQueue newPQueue(void); // create a new priority queue
void deletePQueue(PQueue q); // free a priority queue

void joinPQueue(PQueue q, Item value, int p); // insert a value into the priority queue
Item leavePQueue(PQueue q); // remove item with highest priority from queue

void reorder(PQueue q, Item vertex, int distance); // re-orders the queue when a new entry is added

int updatePQueue(PQueue q, Item v, int newp); // updates a node with a new priority, returns 0 if node wasn't found

void showPQueue(PQueue q); // show the contents of the queue

// predicate functions
int isEmptyPQ(PQueue q); // returns true if queue is empty
