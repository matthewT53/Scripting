/* 
	Author: Matthew Ta
	Date: 3/7/2015
	Description: Prints the strings beginnging with the letter b
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LENGTH 100
#define NEWLINE '\n'
#define NULL_CHAR '\0'
#define LETTER 'b'

int main(void)
{
	char line[MAX_LENGTH], *linePtr = NULL;
	char *newLine = NULL;

	linePtr = fgets(line, MAX_LENGTH, stdin);
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		if (strchr(linePtr, LETTER) != NULL){
			printf("%s.\n", linePtr);
		}
		
		linePtr = fgets(line, MAX_LENGTH, stdin);
	}
	

	return 0;
}
