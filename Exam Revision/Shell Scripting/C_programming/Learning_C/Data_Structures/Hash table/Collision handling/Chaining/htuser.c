/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: User of the hash table ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ht.h"

#define SIZE 10

int main(void)
{
	HashTable ht = newTable(SIZE);

	insertItem(ht, "Yolo");
	insertItem(ht, "Almost holidays");
	insertItem(ht, "Hi, I'm Matthew");
	insertItem(ht, "Yolo.");

	showHashTable(ht);

	removeItem(ht, "Yolo.");
	removeItem(ht, "sdgsdhgksd"); // remvoe osmething not in ht
	showHashTable(ht);

	Item *it = searchItem(ht, "Yolo");
	assert(it != NULL);
	
	it = searchItem(ht, "gdfgdfg");
	assert(it == NULL);

	ht = hashTableExpand(ht, 20);
	assert(ht != NULL);

	insertItem(ht, "Welcome to my new hash table");
	insertItem(ht, "Where will you put me");
	insertItem(ht, "");
	insertItem(ht, "Generate a collision please");
	showHashTable(ht);

	ht = hashTableExpand(ht, 30);

	showHashTable(ht);

	ht = hashTableExpand(ht, 10);
	showHashTable(ht);

	disposeTable(ht);
	return EXIT_SUCCESS;
}
