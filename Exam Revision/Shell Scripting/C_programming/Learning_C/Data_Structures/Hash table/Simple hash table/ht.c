/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: Implementation of the interface for the hash table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ht.h"

typedef struct _hashTableRep{
	int nitems; // number of items in hash table
	int nslots; // numebr of elements in the the hash table
	Item *data; // array of items (strings)
} hashTableRep;

int hash(const Key k, const int size); // hash function converts key to an index

// create a new hash table
HashTable newTable(int N)
{
	int i = 0;
	HashTable ht = malloc(sizeof(hashTableRep));
	assert(ht != NULL);

	ht->data = malloc(sizeof(Item) * N);
	assert(ht->data != NULL);
	ht->nslots = N;
	ht->nitems = 0;
		
	
	for (i = 0; i < N; i++){
		ht->data[i] = NULL;
	}
	return ht;
}

// free a hash table
void disposeTable(HashTable ht)
{
	int i = 0;
	for (i = 0; i < ht->nslots; i++){
		if (ht->data[i] != NULL) { free(ht->data[i]); }
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
	if (ht->data[i] == NULL){
		ht->data[i] = str;
		ht->nitems++;
	}

	else if (key(ht->data[i]) == key(it)){ // update
		strcpy(ht->data[i], it);
		printf("Updating key.\n");
	}
		
	else{
		printf("Collision detected.\n");
	}
}

// search for an item in the hash table
Item *searchItem(HashTable ht, Key k)
{
	int i = hash(k, ht->nslots);
	Item *it = NULL;
	if (ht->data[i] != NULL)
		it = &ht->data[i];
	return it;
}

// remove an item from the hash table
void removeItem(HashTable ht, Key k)
{
	int i = hash(k, ht->nslots);
	if (ht->data[i] != NULL) { ht->nitems--; free(ht->data[i]); ht->data[i] = NULL; }
}

// converts a key into an index
int hash(const Key k, const int size) // universal hashing
{
	int h = 0, a = 31415, b = 21783;
	char *c;
	for (c = k; *c != '\0'; c++) {
		a = a*b % (size - 1);
		h = (a * h + *c) % size;
	}
	return h;
}

// this function doubles the number of slots in the hash table
HashTable hashTableExpand(HashTable ht, int n)
{
	int i = 0;
	HashTable newht = newTable(n); // create the new hash table
	assert(newht != NULL); 
	newht->nslots = n; // new ht now has 2x the num slots
	newht->nitems = 0; // nitems is 0

	// insert all the values into the new ht
	for (i = 0; i < ht->nslots; i++){
		if (ht->data[i] != NULL){ insertItem(newht, ht->data[i]); }
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
	for (i = 0; i < ht->nslots; i++){
		printf("[%d]: %s\n", i, ht->data[i]);
	}
}
