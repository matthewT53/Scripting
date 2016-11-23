/*
	Name: Matthew Ta
	Date: 12/11/2015
	Description: User of the tries ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tries.h"

int main(void)
{
	Trie t = newTrie();
	
	printf("Testing insertion:\n");
	printf("Inserting hello world.\n");
	insertItem(t, "hello world");
	assert(searchItem(t, key("hello world")) != NULL);
	printf("Passed.\n");
	//showTrie(t);
	disposeTrie(t);

	t = newTrie();
	printf("Inserting cat then cats.\n");
	insertItem(t, "cat");
	insertItem(t, "cats");
	assert(searchItem(t, key("cat")) != NULL && searchItem(t, key("cats")) != NULL);
	printf("Passed.\n");

	printf("Testing delete function, removing cats.\n");
	removeItem(t, key("cats"));
	assert(searchItem(t, key("cats")) == NULL);
	printf("Passed.\n");

	printf("Inserting dads.\n");
	insertItem(t, "dads");
	assert(searchItem(t, key("dads")) != NULL);
	// showTrie(t);
	printf("Passed.\n");

	printf("Inserting dad.\n");
	insertItem(t, "dad");
	assert(searchItem(t, key("dad")) != NULL);
	printf("Passed.\n");

	printf("Inserting can.\n");
	insertItem(t, "can");
	//showTrie(t);
	assert(searchItem(t, key("can")) != NULL);
	printf("Passed.\n");

	printf("Inserting can't.\n");
	insertItem(t, "can't");
	assert(searchItem(t, key("can't")) != NULL);
	printf("Passed.\n");

	printf("Inserting cans.\n");
	insertItem(t, "cans");
	assert(searchItem(t, key("cans")) != NULL);
	printf("Passed.\n");

	printf("Inserting cast.\n");
	insertItem(t, "cast");
	assert(searchItem(t, key("cast")) != NULL);
	printf("Passed.\n");

	showTrie(t);
	disposeTrie(t);

	printf("Passed all tests, you are awesome.\n");

	return EXIT_SUCCESS;
}
