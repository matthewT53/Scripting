/*
	Author: Matthew Ta
	Date: 2/7/2015
	Description: Experimentation with the const qualifier
*/

#include <stdio.h>
#include <stdlib.h>

void function(const int *value);

int main(void)
{
	int x = 10;
	function(&x);
	return 0;
}

void function(const int *value)
{
	int y = 5;
	y = *value;
	printf("%d.\n", y);
}
