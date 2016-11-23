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

#define MAX_LENGTH 100
#define DELIMITER " "

// constants for various characters
#define NULL_CHAR '\0'
#define SPACE ' '
#define NEWLINE '\n'

void printReverse(char *);
void shiftPointer(char *);

int main(void)
{
	char sentence[MAX_LENGTH], *ptr_to_input = NULL, *ptr_to_newline = NULL;
	char *token = NULL;
	
	printf("Enter a sentence: \n");
	ptr_to_input = fgets(sentence, MAX_LENGTH, stdin);

	// remove new line char from sentence
	ptr_to_newline = strchr(ptr_to_input, NEWLINE);
	*ptr_to_newline = '\0';
	token = strtok(ptr_to_input, DELIMITER);
	// remove the first word from the line
	shiftPointer(ptr_to_input);

	printReverse(ptr_to_input);
	printf("%s\n", token);
	return 0;
}

void printReverse(char *string)
{
	char *token = NULL;
	
	token = strtok(NULL, DELIMITER);
	shiftPointer(string);
	if (token != NULL){
		printReverse(string);
		printf("%s ", token);
	}
}

void shiftPointer(char *string)
{
	while (*string != NULL_CHAR){
		string++;
	}
	string++;
}
