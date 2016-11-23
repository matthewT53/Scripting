/*
	Name: Matthew Ta
	Date: 11/11/2015
	Description: User of the heap ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

#define HEAP_SIZE 10

int main(void)
{
	Heap h = newHeap(HEAP_SIZE);

	printf("Testing inertion into the heap.\n");
	insertItem(h, 15); // test inserting items
	insertItem(h, 14);
	insertItem(h, 90);
	insertItem(h, 5);

	insertItem(h, 100);
	insertItem(h, 0);
	insertItem(h, 6);
	insertItem(h, 8);

	insertItem(h, 190);
	insertItem(h, 67);
	showHeap(h);
	// insertItem(h, 909);
	
	printf("Testing deletion from heap.\n");
	Item it = deleteItem(h);
	assert(it == 190);
	assert(getNumItems(h) == 9);
	showHeap(h);
	
	it = deleteItem(h);
	assert(it == 100);
	assert(getNumItems(h) == 8);
	showHeap(h);

	disposeHeap(h);
	return EXIT_SUCCESS;
}
