/*
	Author: Matthew Ta
	Date: 2/7/2015
	Description: Search for occurences of a string
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LENGTH 100

#define NULL_CHAR '\0'
#define NEWLINE '\n'

int main(void)
{
	char line[MAX_LENGTH], *linePtr = NULL;
	char search[MAX_LENGTH], *searchString = NULL;
	char *searchPtr = NULL;
	char *newLine = NULL;

	// get the line and the search string
	printf("Enter a line of text:\n");
	linePtr = fgets(line, MAX_LENGTH, stdin);
	newLine = strchr(linePtr, NEWLINE);
	*newLine = NULL_CHAR;
	newLine = NULL;
	assert(linePtr != NULL);

	printf("Enter the search string: \n");
	searchString = fgets(search, MAX_LENGTH, stdin);
	newLine = strchr(searchString, NEWLINE);
	*newLine = NULL_CHAR;
	newLine = NULL;
	assert(searchString != NULL);

	// find occurences of the search string inside the line
	searchPtr = strstr(linePtr, searchString);
	assert(searchPtr != NULL);

	while (searchPtr != NULL){
		printf("%s\n", searchPtr);
		searchPtr = strstr(searchPtr + 1, searchString);
	}

	return 0;
}
