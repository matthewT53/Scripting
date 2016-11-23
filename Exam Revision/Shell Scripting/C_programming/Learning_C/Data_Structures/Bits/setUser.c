/*
	Name: Matthew Ta
	Date: 14/11/2015
	Description: User of the bitmap set ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bitmap.h"

#define MAX_NUMBER 100

int main(void)
{
	Bits b = newSet(MAX_NUMBER);

	// test inserting items
	printf("Testing insertion:\n");
	insertItem(b, 15);
	insertItem(b, 90);
	insertItem(b, 0); // ends up storing 32
	// insertItem(b, 142423523); // causes seg faults
	insertItem(b, 76);
	insertItem(b, 45);
	insertItem(b, 35);
	insertItem(b, 89);
	showSetSorted(b);
	showBits(b);
	
	// test removing items
	printf("Testing removal:\n");
	removeItem(b, 76);
	removeItem(b, 90);
	showSet(b);

	// test searching items
	printf("Testing searching:\n");
	int res = searchItem(b, 89);
	assert(res != 0);
	res = searchItem(b, 17);
	assert(res == 0);

	// testing power of two function
	printf("128 is a power of two: %s\n", (isPowerTwo(128)) ? "TRUE" : "FALSE");
	printf("56 is a power of two: %s\n", (isPowerTwo(56)) ? "TRUE" : "FALSE");

	// testing the union of two sets
	printf("Testing union of sets:\n");
	Bits a = newSet(MAX_NUMBER);
	insertItem(a, 5);
	insertItem(a, 10);
	insertItem(a, 35);
	insertItem(a, 19);
	insertItem(a, 55);
	showSetSorted(a);
	showBits(a);
	
	Bits c = joinSets(a, b);
	showSetSorted(c);
	showBits(c);

	// testing the intersection function
	printf("Testing intersection of sets:\n");
	c = elemsInCommon(a,b);
	showSetSorted(c);
	showBits(c);

	disposeSet(a);
	disposeSet(b);
	disposeSet(c);
	return EXIT_SUCCESS;
}
