/*
	Name: Matthew Ta
	Date: 11/11/2015
	Description: Implementation of the heap ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

#define LESS(x, y) (x < y) // determines whether x is < y
#define NO_ITEM -99999 // distinguish empty array slots

// Note: Heap starts from index 1 and index 0 is always empty

typedef struct _heapRep{
	Item *items; // array of items
	int nitems; // used as index as well
	int nslots; // # items in array
} heapRep;

void fixUp(Item *a, const int index); // fixes heap after insertion
void fixDown(Item *a, const int rootIndex, const int maxItems); // fixes heap after deleton from root 
void swap(Item *a, const int i, const int j); // swaps two elements

// create a new heap structure
Heap newHeap(int n)
{
	int i = 0;
	Heap hp = malloc(sizeof(heapRep));
	assert(hp != NULL); 

	// create the array for the heap
	hp->items = malloc(sizeof(Item) * n + 1);
	hp->nitems = 0;
	hp->nslots = n;

	// initialise the heap
	for (i = 0; i < n; i++){
		hp->items[i] = NO_ITEM;
	}
	return hp;
}

// free the heap structure
void disposeHeap(Heap hp)
{
	if (hp != NULL){
		free(hp->items);
		free(hp);
	}
}

// insert an item into the heap
void insertItem(Heap hp, Item it)
{
	assert(hp->nitems < hp->nslots);
	hp->nitems++;
	hp->items[hp->nitems] = it;	// insert item
	fixUp(hp->items, hp->nitems); // fix the heap
}

// repairs the heap structure after inserting
void fixUp(Item *a, const int index)
{
	int i = index;
	while (i > 1 && !LESS(a[i], a[i/2])){
		swap(a, i, i/2);
		i /= 2; // move up to compare with parent
	}
}

// swaps two elements
void swap(Item *a, const int i, const int j)
{
	Item temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

// search for an item in the heap
Item *searchItem(Heap hp, Item it)
{
	int i = 0;
	Item *found = NULL;
	for (i = 1; i <= hp->nitems; i++){
		if (hp->items[i] == it){
			found = &hp->items[i];
			break;
		}
	}
	return found;
}

// delete the item at top of heap
Item deleteItem(Heap hp)
{
	Item top = hp->items[1]; // get the root
	hp->items[1] = hp->items[hp->nitems]; // replace by bottom most and right most value
	hp->items[hp->nitems] = NO_ITEM; // delete the replacement node
	hp->nitems--;
	fixDown(hp->items, 1, hp->nitems);
	return top;
}

// repair heap after deletion
void fixDown(Item *a, const int rootIndex, const int maxItems)
{
	int i = rootIndex, j = rootIndex;
	while ((i * 2) <= maxItems){
		i = 2 * j; // move one level down the heap
		if (LESS(a[i + 1], a[i]) && LESS(a[j], a[i])){ swap(a, i, j); j = i; } // left child > right child
		else if (LESS(a[i], a[i + 1]) && LESS(a[j], a[i + 1])){ swap(a, i + 1, j); j = i + 1; } // right child > left child
		else{ break; } // the value is now larger than both its children
	}
}

// get # items in heap
int getNumItems(Heap hp)
{
	return hp->nitems;
}

// output the heap
void showHeap(Heap hp)
{
	int i = 0;
	printf("nitems = %d.\n", hp->nitems);
	printf("nslots = %d.\n", hp->nslots);
	
	for (i = 1; i <= hp->nitems; i++){
		printf("[%d]: %d\n", i, hp->items[i]);
	}
}




