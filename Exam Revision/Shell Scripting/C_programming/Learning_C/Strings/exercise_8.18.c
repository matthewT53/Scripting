/* 
	Author: Matthew Ta
	Date: 2/7/2015
	Descriptions: Counts the occurences of a character
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
	char c, objectsRead = 0;
	char *searchPtr = NULL;
	char *newLine = NULL;
	int total_occurences = 0;
	
	// input the char to search for
	printf("Enter a character to search for: \n");
	objectsRead = scanf("%c", &c);
	assert(objectsRead > 0);
	// input several lines of text
	printf("Now input the lines of text: \n");
	linePtr = fgets(line, MAX_LENGTH, stdin);
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		// check for the occurences of the character
		searchPtr = strchr(linePtr, c);
		while (searchPtr != NULL){
			total_occurences++;
			searchPtr = strchr(searchPtr + 1, c);
		}
		linePtr = fgets(line, MAX_LENGTH, stdin);
	}

	printf("Total occurences of %c was: %d.\n", c, total_occurences);

	return 0;
}
