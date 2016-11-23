/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: Implementation of the interface for the hash table (Double hashing)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define eq(x,y) (strcmp(x,y) == 0) // macro to detect whether two strings are equal
#define USED_SLOT(x) (x != NULL) 

#define TRUE 1
#define FALSE 0

#include "ht.h"

typedef struct _hashTableRep{
	int nitems; // number of items in hash table
	int nslots; // numebr of elements in the the hash table
	Item *data; // array of items (strings)
	int nhash2; // prime number for secondary hash function
} hashTableRep;

int hash(const Key k, const int size); // hash function converts key to an index
int hash2(const Key k, const int size); // secondary hash function
int findPrime(int n); // finds a suitable prime number

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
	ht->nhash2 = findPrime(N); // finds a suitable prime for hash2()
	
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
	int inc = hash2(key(it), ht->nhash2); // generate another hash of the key to use as an increment
	int j = 0, index = 0;

	// string data stuff
	int len = strlen(it);
	char *str = malloc(sizeof(char) * len + 1);
	assert(str != NULL);
	strcpy(str, it);
	
	for (j = 0; j < ht->nslots; j += inc){ // linear probing
		index = (j + i) % ht->nslots; // incase we need to wrap around
		if (key(ht->data[index]) == NULL){ ht->nitems++; break; } // add item to hash table
		else if ( eq(key(ht->data[index]), key(it)) ){ break; } // update
	}
	ht->data[index] = str;
}

// search for an item in the hash table
Item *searchItem(HashTable ht, Key k)
{
	int i = 0, j = 0;
	int h = hash(k, ht->nslots); // get an index
	int inc = hash2(k, ht->nhash2); // get an increment
	Item *it = NULL;

	for (j = 0; j < ht->nslots; j += inc){ // scan for the item if we need to
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

// secondary hash function
int hash2(const Key k, const int mFactor)
{
	int h = 0;
	char *c = NULL;
	
	for (c = k; *c != '\0'; c++){
		h = (h + (*c)) * (*c);
	}
	return h % mFactor + 1;
}

// finds a suitable prime number that is < n
int findPrime(int n)
{
	int p = 0; // potential prime number
	int f = 0; // p's factors
	int isPrime = FALSE; // flag for whether p is prime or not
	
	for (p = n - 1; p > 0; p--){ // find a potential prime num < N
		isPrime = TRUE;
		for (f = 2; f < p; f++){ // loop through p's factors (0 and 1 cannot be used for f)
			if (p % f == 0){ // found a factor for p other than 1 and itself
				isPrime = FALSE;
				break;
			}
		}

		if (isPrime){ // number is prime, exit loop
			break;
		}
	}
	return p;
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
	printf("Load = %.2f\n", (float) ht->nitems / (float) ht->nslots);
	for (i = 0; i < ht->nslots; i++){
		printf("[%03d]: %s\n", i, ht->data[i]);
	}
}
