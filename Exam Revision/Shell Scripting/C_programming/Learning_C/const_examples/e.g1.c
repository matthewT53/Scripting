/*
	Author: Matthew Ta
	Date: 5/7/2015
	Description: examples with using the const qualifier
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	const int *xPtr;
	int *yPtr = NULL;
	int j = 6;
	int h = 9;
	
	// able to change where xPtr points to
	xPtr = &j;
	
	// cannot modify the value of xPtr
	// ERROR: *xPtr = 5;
	
	// ERROR: Down qualification yPtr = xPtr;
	yPtr = (int *) xPtr;
	printf("%d\n", *yPtr);
	return 0;
}
