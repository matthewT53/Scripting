/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: Implementation of the interface for the hash table
	Collision resolution: chaining
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ht.h"
#include "linkList.h"

typedef struct _hashTableRep{
	int nitems; // number of items in hash table
	int nslots; // number of elements in the the hash table
	List *data; // array of lists
} hashTableRep;

int hash(const Key k, const int size); // hash function converts key to an index

// create a new hash table
HashTable newTable(int N)
{
	int i = 0;
	HashTable ht = malloc(sizeof(hashTableRep));
	assert(ht != NULL);

	ht->data = malloc(sizeof(List) * N);
	assert(ht->data != NULL);
	ht->nslots = N;
	ht->nitems = 0;
		
	// set each slot as empty
	for (i = 0; i < N; i++){
		ht->data[i] = createList();
	}
	return ht;
}

// free a hash table
void disposeTable(HashTable ht)
{
	int i = 0;
	for (i = 0; i < ht->nslots; i++){
		deleteList(ht->data[i]); ht->data[i] = NULL;
	}

	free(ht);
}

// insert an item into the hash table
void insertItem(HashTable ht, Item it)
{
	int i = hash(key(it), ht->nslots);
	int len = strlen(it);
	char *str = malloc(sizeof(char) * len + 1);
	strcpy(str, it);
	addNode(ht->data[i], str);
	ht->nitems++;
}

// search for an item in the hash table
Item *searchItem(HashTable ht, Key k)
{
	int i = hash(k, ht->nslots);
	Item *it = NULL;
	it = findNode(ht->data[i], k);
	return it;
}

// remove an item from the hash table
void removeItem(HashTable ht, Key k)
{
	int i = hash(k, ht->nslots);
	int success = deleteNode(ht->data[i], k);
	if (success) { ht->nitems--; }
}

// converts a key into an index
int hash(const Key k, const int size) // universal hashing
{
	int h = 0, a = 31415, b = 21783;
	char *c;
	for (c = k; *c != '\0'; c++){
		a = a*b % (size - 1);
		h = (a * h + *c) % size;
	}
	return h;
}

// this function doubles the number of slots in the hash table
HashTable hashTableExpand(HashTable ht, int n)
{
	int i = 0, max = 0, j = 0;
	Item *data = NULL;
	HashTable newht = newTable(n); // create the new hash table
	assert(newht != NULL); 
	newht->nslots = n; // new ht now has 2x the num slots
	newht->nitems = 0; // nitems is 0

	// insert all the values into the new ht
	for (i = 0; i < ht->nslots; i++){
		max = getLength(ht->data[i]); // get length of the list
		data = copyListArray(ht->data[i]); // copy the old list into a temp array
		for (j = 0; j < max; j++){ // insert the data into new list
			insertItem(newht, data[j]);
		}
		if (data != NULL) { free(data); } // free the array
		data = NULL;
	}

	disposeTable(ht);
	return newht;
}

// output the hash table
void showHashTable(HashTable ht)
{
	int i = 0;
	
	printf("Number of items: %d.\n", ht->nitems);
	printf("Number of slots: %d.\n", ht->nslots);
	printf("Load: %.2f\n", (float) (ht->nitems) / (float) (ht->nslots));
	for (i = 0; i < ht->nslots; i++){
		printf("[%02d]: ", i);
		printList(ht->data[i]);
	}
}
