/*
	Name: Matthew Ta
	Date: 9/11/2015
	Desciption: Uses the symbol table ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "symTable.h"

#define SIZE 10

int main(void)
{
	sTab st = newTable(SIZE);
	printTable(st);
	
	printf("Testing insertion.\n");
	insertItem(st, 5, 18);
	insertItem(st, 8, 15);
	insertItem(st, 1, 19);
	printTable(st);
	
	printf("Testing inserting values with out of bound keys.\n");
	insertItem(st, 89, 40);
	insertItem(st, 450, 0);
	printTable(st);

	printf("Testing removing values.\n");
	removeItem(st, 16);
	removeItem(st, 15);
	printTable(st);

	printf("Testing searching values.\n");
	insertItem(st, 546, 17);
	insertItem(st, 345, 14);
	insertItem(st, 123546, 12);
	printTable(st);

	Item *it = searchItem(st, 14);
	printf("it = %d.\n", *it);

	it = searchItem(st, 15);
	assert(it == NULL);	

	disposeTable(st);
	return EXIT_SUCCESS;
}
