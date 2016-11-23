/*
	Name: Matthew Ta
	Date: 30/5/2016
	Description: Driver to test the trie implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "trie.h"

#define TRUE 1
#define FALSE 0

int main(void)
{
	Trie t = newTrie(FALSE);
	
	printf("Before deletion:\n");
	addword(t, "hello");
	addword(t, "mate");
	addword(t, "how");
	addword(t, "are");
	addword(t, "dogs");
	addword(t, "matthew");
	addword(t, "straithfield");
	addword(t, "cat");
	addword(t, "caton");
	addword(t, "catonate");

	showTrie(t);

	printf("After deletion:\n");
	assert(checkword(t, "cat") == TRUE);
	assert(checkword(t, "caty") == FALSE);
	assert(checkword(t, "catonate") == TRUE);
	assert(checkword(t, "dogs") == TRUE);
	assert(checkword(t, "straithfield") == TRUE);
	assert(checkword(t, "arabia") == FALSE);
	assert(checkword(t, "concensus") == FALSE);
	
	assert(checkword(t, "hello") == TRUE);
	assert(checkword(t, "are") == TRUE);
	delword(t, "hello");
	assert(checkword(t, "hello") == FALSE);
	delword(t, "are");
	assert(checkword(t, "are") == FALSE);

	showTrie(t);

	deleteTrie(t);

	return EXIT_SUCCESS;
}
