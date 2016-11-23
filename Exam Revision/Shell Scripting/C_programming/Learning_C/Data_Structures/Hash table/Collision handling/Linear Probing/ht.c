/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: Implementation of the interface for the hash table (Linear probing)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define eq(x,y) (strcmp(x,y) == 0) // macro to detect whether two strings are equal
#define USED_SLOT(x) (x != NULL) 

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
	assert(ht->nitems < ht->nslots);
	int i = hash(key(it), ht->nslots);
	int len = strlen(it);
	int j = 0, index = 0;
	char *str = malloc(sizeof(char) * len + 1);
	assert(str != NULL);
	strcpy(str, it);
	
	for (j = 0; j < ht->nslots; j++){ // linear probing
		index = (j + i) % ht->nslots; // incase we need to wrap around
		if (key(ht->data[index]) == NULL){ ht->nitems++; break; } // add item to hash table
		else if ( eq(key(ht->data[index]), key(it)) ){ break; } // update
	}

	ht->data[index] = str; // there will always be a spot for the item unless hash table is full
}

// search for an item in the hash table
Item *searchItem(HashTable ht, Key k)
{
	int i = 0, j = 0;
	int h = hash(k, ht->nslots); // get an index
	Item *it = NULL;

	for (j = 0; j < ht->nslots; j++){ // scan for the item if we need to
		i = (h + j) % ht->nslots;
		if ( USED_SLOT(key(ht->data[i])) && eq(key(ht->data[i]), k) ) { it = &ht->data[i]; break; }
	}

	return it;
}

// remove an item from the hash table
void removeItem(HashTable ht, Key k)
{
	int i = 0, j = 0;
	int h = hash(k, ht->nslots);

	for (j = 0; j < ht->nslots; j++){ // scan for item with key k
		i = (h + j) % ht->nslots;
		if (USED_SLOT(ht->data[i])){ // check if item is NULL
			if ( eq(key(ht->data[i]), k) ){ // check if item is equal to key
				free(ht->data[i]); // free the item
				ht->data[i] = NULL;
				ht->nitems--;
				break;
			}
		}
	}

	// need to ensure that there are no NULL items in middle of probe path
	for (j = i + 1; ht->data[j] != NULL; j = (j + 1) % ht->nslots){
		Item it = ht->data[j];
		ht->data[j] = NULL;
		ht->nitems--;
		insertItem(ht, it);
	}
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
		printf("[%02d]: %s\n", i, ht->data[i]);
	}
}
