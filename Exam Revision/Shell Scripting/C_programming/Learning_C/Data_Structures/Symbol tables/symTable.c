/*
	Name: Matthew Ta
	Date: 9/11/2015
	Description: Implementation of the interface for the symbol table
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "symTable.h"

#define validIndex(i) (i > 0 && i < st->n)

#define UNUSED -9999999
#define KEY_SHIFT 10

typedef struct _symbolTable{
	Item *a; // collection of items
	int n; // # items
} symbolTable; 

typedef int Index;

Index keyToIndex(Key k); // function that converts a key -> index

sTab newTable(int n)
{
	int i = 0;
	sTab st = malloc(sizeof(symbolTable));
	assert(st != NULL);
	st->a = malloc(sizeof(Item) * n);
	st->n = n;

	for (i = 0; i < n; i++){
		st->a[i] = UNUSED;
	}
	
	return st;
}

void disposeTable(sTab st)
{
	free(st->a);
	free(st);
}

void insertItem(sTab st, Item it, Key k)
{
	Index i = keyToIndex(k);
	if (st != NULL && st->a != NULL){
		if (validIndex(i) && st->a[i] == UNUSED){
			st->a[i] = it;
		}
	}
}

void removeItem(sTab st, Key k)
{
	Index i = keyToIndex(k);
	if (st != NULL && st->a != NULL){
		if (validIndex(i)) { st->a[i] = UNUSED; }
	}
}

Item *searchItem(sTab st, Key k)
{
	Index i = keyToIndex(k);
	Item *it = NULL;
	if (st != NULL && st->a != NULL){
		if (validIndex(i) && st->a[i] != UNUSED) { it = &(st->a[i]); }
	}
	return it;
}

Index keyToIndex(Key k)
{
	return (k - KEY_SHIFT);
}

void printTable(sTab st)
{
	int i = 0;
	printf("Size: %d.\n", st->n);
	if (st != NULL && st->a != NULL){
		for (i = 0; i < st->n; i++){ printf("[%d]: %d\n", i, st->a[i]); }
		printf("\n");
	}
}




