/* 
	Author: Matthew Ta
	Date: 2/7/2015
	Description: Counts the number of occurences of a substring
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
	char search[MAX_LENGTH], *searchString = NULL, *searchPtr = NULL;
	char *newLine = NULL;
	int total_occurences = 0;
	
	printf("Enter a search string: \n");
	searchString = fgets(search, MAX_LENGTH, stdin);
	newLine = strchr(searchString, NEWLINE);
	*newLine = NULL_CHAR;
	
	// input several lines of text
	printf("Now input the lines of text: \n");
	linePtr = fgets(line, MAX_LENGTH, stdin);
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		// check for the occurences of the substring
		searchPtr = strstr(linePtr, searchString);
		while (searchPtr != NULL){
			total_occurences++;
			searchPtr = strstr(searchPtr + 1, searchString);
		}

		linePtr = fgets(line, MAX_LENGTH, stdin);
	}

	printf("Total occurences of %s was: %d.\n", searchString, total_occurences);

	return 0;
}
