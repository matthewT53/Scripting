/*
	Name: Matthew Ta
	Date: 24/11/2015
	Description: Exp with realloc and calloc
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* calloc(# elements, sizeof(each element) */

int main(void)
{
	int *a = calloc(15, sizeof(int)); // also initialises each element to 0
	assert(a != NULL);

	printf("Size a: %lu\n", sizeof(a)); // ptrs are 8 bytes
	a = realloc(a, 30); // note: new size must be greater than the old size if old content is ot be left unchanged
	assert(a != NULL);	

	return EXIT_SUCCESS;
}
