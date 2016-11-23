/* 
	Name: Matthew Ta
	Date: 3/7/2015
	Description: Counts the number of words in a string
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define DELIMITER " "

#define NEWLINE '\n'
#define NULL_CHAR '\0'

int main(void)
{
	char line[MAX_LENGTH], *linePtr = NULL;
	char *token = NULL;
	char *newLine = NULL;
	int total_words = 0;

	// input the lines
	printf("Enter some lines of text: \n");
	linePtr = fgets(line, MAX_LENGTH, stdin);
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		token = strtok(linePtr, DELIMITER);
		while (token != NULL){
			total_words++;
			token = strtok(NULL, DELIMITER);
		}
		
		linePtr = fgets(line, MAX_LENGTH, stdin);
	}

	printf("Total number of words: %d.\n", total_words);

	return 0;
}
