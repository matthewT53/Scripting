/*
	Name: Matthew Ta
	Date: 14/11/2015
	Description: Bit map rep of sets
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "bitmap.h"

// boolean constants
#define TRUE 1
#define FALSE 0

#define NBITS 8 // number of bits in a word
#define NBITS_WORD 32 // 32 bits in a word

#define LEFT_MOST_BIT (pow(2,31))

// helper functions for inserting and deleting
void setBit(Bits b, int it); // sets a bit to 1
void unsetBit(Bits n, int it); // sets a bit to 0
Bits unionSets(Bits a, Bits b); // joins two sets together
Bits intersection(Bits a, Bits b); // finds the common elements
void detNumElements(Bits a); // determines # elements (inefficient)

typedef struct _setRep{
	Word *words;
	int nelems; // number of elements in the set
	int nwords; // # words to hold the elements
	int maxValue; // largest value the set can hold
} setRep;

// create a new set
Bits newSet(int n)
{
	int i = 0;
	Bits b = malloc(sizeof(setRep));
	assert(b != NULL);

	// determine how many words to allocate
	float a = n / NBITS_WORD;
	int words = (int) ceil(a);

	b->words = malloc(sizeof(unsigned int) * words); // allocate space for the words
	for (i = 0; i < words; i++){ // can just use calloc but maloc is cooler
		b->words[i] = 0;
	}
	assert(b->words != NULL);
	b->nelems = 0;
	b->nwords = words;
	b->maxValue = n;
	return b; 
}

// disposes a set
void disposeSet(Bits b)
{
	free(b->words);
	free(b);
}

// insert into set
void insertItem(Bits b, int it) // O(1) 
{	
	assert(b != NULL && b->words != NULL);
	setBit(b, it);
	b->nelems++;
}

// remove an item
void removeItem(Bits b, int it) // O(1)
{
	assert(b != NULL && b->words != NULL);
	unsetBit(b, it);
	b->nelems--;
}

// search for an item
int searchItem(Bits b, int it)
{
	assert(b != NULL && b->words != NULL);
	Word w = it / NBITS_WORD;
	Word bit = it % NBITS_WORD;
	Word mask = 1;
	int res = FALSE;
	
	mask = mask << (NBITS_WORD - bit);
	res = mask & b->words[w];
	return res;
}

// set a bit
void setBit(Bits b, int it)
{
	Word mask = 1;
	Word w = it / NBITS_WORD; // determine which word in number is in
	Word bit = it % NBITS_WORD; // calculate which bit in the word	
	
	mask = mask << (NBITS_WORD - bit); // move the 1 to a better pos
	b->words[w] |= mask; // set the bit
}

// unset a bit
void unsetBit(Bits b, int it)
{
	Word mask = 1;
	Word w = it / NBITS_WORD;
	Word bit = it % NBITS_WORD;

	mask = mask << (NBITS_WORD - bit); 
	mask = ~mask; // flip bits
	b->words[w] &= mask; // unset the bit
}

// determines if a number is a power of two
int isPowerTwo(Word w)
{
	Word temp = w - 1; // binary subraction by one
	temp = temp & w; // and operation
	return (temp == 0) ? TRUE : FALSE; 
}

// joins two sets together
Bits joinSets(Bits a, Bits b)
{
	Bits c = NULL;
	// pre-condition they have to be of the same size
	
	if (a != NULL && b != NULL){
		if (a->nwords == b->nwords){
			c = unionSets(a, b);
			detNumElements(c);
		}
	}
	return c;
}

// union of two sets
Bits unionSets(Bits a, Bits b) // intersection is similar, just replace | with &
{
	int i = 0;
	Bits c = newSet(a->maxValue);
	for (i = 0; i < a->nwords; i++){
		c->words[i] = a->words[i] | b->words[i];
	}
	return c;
}

// finds elements in common between two sets
Bits elemsInCommon(Bits a, Bits b)
{
	Bits c = NULL;
	if (a != NULL && b != NULL){
		if (a->nwords == b->nwords){
			c = intersection(a, b);
			detNumElements(c);
		}
	}
	return c;
}

// intersection of two sets
Bits intersection(Bits a, Bits b)
{
	Bits c = newSet(a->maxValue);
	int i = 0;

	for (i = 0; i < a->nwords; i++){
		c->words[i] = a->words[i] & b->words[i];
	}
	return c;
}

// returns # elements
int getNumElements(Bits a)
{
	return a->nelems;
}

// determine the # of elements
void detNumElements(Bits a)
{
	int i = 0, j = 0;
	Word mask, res;
	a->nelems = 0; // reset so we can calculate again

	for (i = 0; i < a->nwords; i++){
		for (j = 0; j < NBITS_WORD; j++){
			mask = (Word) LEFT_MOST_BIT;
			mask = mask >> j;
			res = a->words[i] & mask;
			if (res) { a->nelems++; } // found an element
		}
	}
}

// print the set
void showSet(Bits b)
{
	int i = 0, j = 0, number = 0;
	Word mask, res;

	printf("nwords = %d\n", b->nwords);
	printf("nelems = %d\n", b->nelems);
	for (i = 0; i < b->nwords; i++){
		for (j = 0; j < NBITS_WORD; j++){
			mask = 1;
			mask = mask << j;
			res = b->words[i] & mask;
			if (res){ // if a one was found print the number
				number = (i * NBITS_WORD) + (NBITS_WORD - j);
				printf("[%d]->", number);
			}
		}
	}
	printf("[X]\n");
}

// print the set in sorted order
void showSetSorted(Bits b)
{
	int i = 0, j = 0, number = 0;
	Word mask, res;

	printf("nwords = %d\n", b->nwords);
	printf("nelems = %d\n", b->nelems);
	for (i = 0; i < b->nwords; i++){
		for (j = 0; j < NBITS_WORD; j++){
			mask = (unsigned int) LEFT_MOST_BIT;
			mask = mask >> j;
			res = b->words[i] & mask;
			if (res){ // if a one was found print the number
				number = (i * NBITS_WORD) + (j + 1); // since j only goes up to 31
				printf("[%d]->", number);
			}
		}
	}
	printf("[X]\n");
}

// print the bits
void showBits(Bits b)
{
	int i = 0, j = 0;
	Word mask, res;

	printf("nwords = %d\n", b->nwords);
	printf("nelems = %d\n", b->nelems);
	for (i = 0; i < b->nwords; i++){
		printf("Word [%d]: ", i);
		printf("[");
		for (j = 0; j < NBITS_WORD; j++){
			mask = (unsigned int) LEFT_MOST_BIT;
			mask = mask >> j;
			res = b->words[i] & mask;
			printf("%d", (res) ? 1 : 0);
		}
		printf("]\n");
	}
	printf("\n");


}

