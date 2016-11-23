/*
	Author: Matthew Ta
	Date: 1/7/2015
	Description: Prints a sentence in reverse
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main(void)
{
	char string1[15] = "hello friend";
	char string2[12] = "wabba flabba";
	
	printf("Before copying: \nstring1: %s\nstring2: %s\n", string1, string2);
	strcpy(string1, string2);
	printf("After copying:\nstring1: %s\nstring2: %s\n", string1, string2);


	return 0;
}
