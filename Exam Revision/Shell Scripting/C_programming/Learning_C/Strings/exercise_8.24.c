/*
	Author: Matthew Ta
	Date: 3/7/2015
	Description: Prints strings ending with 'ed'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define NEWLINE '\n'
#define NULL_CHAR '\0'
#define LETTERS "ed"
#define DIFFERENCE 2

int main(void)
{
	char line[MAX_LENGTH], *linePtr = NULL;
	char *newLine = NULL, *nullChar = NULL;
	char *findLetters = NULL, *previousPtr = NULL;

	linePtr = fgets(line, MAX_LENGTH, stdin);
	
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		findLetters = strstr(linePtr, LETTERS);

		// in case ed is in the middle of the string
		while (findLetters != NULL){
			previousPtr = findLetters;
			findLetters = strstr(findLetters + 1, LETTERS);
		}
		
		findLetters = previousPtr;
		nullChar = strchr(linePtr, NULL_CHAR);
		if ((int) (nullChar - findLetters) == DIFFERENCE){
			printf("[OUTPUT]: %s\n", linePtr);
		}
		
		linePtr = fgets(line, MAX_LENGTH, stdin);
	}



	return 0;
}
