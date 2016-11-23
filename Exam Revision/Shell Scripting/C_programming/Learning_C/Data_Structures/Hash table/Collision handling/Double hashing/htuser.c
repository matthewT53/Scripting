/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: User of the hash table ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ht.h"

#define SIZE 7

int main(void)
{
	HashTable ht = newTable(SIZE);
	
	insertItem(ht, "Friend"); // insert items into ht
	insertItem(ht, "Yolo");
	insertItem(ht, "Lookin fors for the holidays"); 

	showHashTable(ht);
	removeItem(ht, "Friend"); // remove item in ht
	removeItem(ht, "asbdfb"); // remove item not in ht
	showHashTable(ht);

	insertItem(ht, "Matthew");
	insertItem(ht, "Matthew"); // collision
	showHashTable(ht);

	Item *it = searchItem(ht, "Matthew"); // search for item in ht
	assert(it != NULL);
	
	it = searchItem(ht, "friend"); // search for item not in ht
	assert(it == NULL);
	printf("it = %p\n", it);
		
	ht = hashTableExpand(ht, 127);
	showHashTable(ht);

	disposeTable(ht);
	return EXIT_SUCCESS;
}


