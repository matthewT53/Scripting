/*
	Name: Matthew Ta
	Date: 11/11/2015
	Desciption: Interface for a heap
*/

typedef int Item; // define Item to be an int type

typedef struct _heapRep *Heap; // ptr to heap structure

Heap newHeap(int n); // create a heap for n items
void disposeHeap(Heap hp); // disposes a heap

void insertItem(Heap hp, Item it); // insert an item into the heap
Item *searchItem(Heap hp, Item it); // search for an item in the heap
Item deleteItem(Heap hp); // remove an item from the top of heap

// may also want to implement a function that allows arbitrary deletions

// getor functions
int getNumItems(Heap hp);

void showHeap(Heap hp); // output the heap
