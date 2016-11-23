/*
	Name: Matthew Ta
	Date: 2/7/2015
	Description: Counts the number of times each letter in the alphabet appears in the lines of input
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LENGTH 100
#define ALPHABET_SIZE 26

#define NULL_CHAR '\0'
#define NEWLINE '\n'
#define START_CHAR_LOWER 'a'

void printResults(const int *total);
void lowerString(char *s1);

int main(void)
{
	char line[MAX_LENGTH], *linePtr = NULL;
	char *searchPtr = NULL;
	char *newLine = NULL;
	int totalInAlphabet[ALPHABET_SIZE] = {0}, i = 0;
	
	// input several lines of text
	printf("Input the lines of text: \n");
	linePtr = fgets(line, MAX_LENGTH, stdin);
	while (linePtr != NULL){
		newLine = strchr(linePtr, NEWLINE);
		*newLine = NULL_CHAR;
		lowerString(linePtr);
		// check for the occurences of the character
		for (i = 0; i < ALPHABET_SIZE; i++){
			searchPtr = strchr(linePtr, START_CHAR_LOWER + i);
			while (searchPtr != NULL){
				totalInAlphabet[i]++;
				searchPtr = strchr(searchPtr + 1, START_CHAR_LOWER + i);
			}
		}

		linePtr = fgets(line, MAX_LENGTH, stdin);
	}

	printResults(totalInAlphabet);
	return 0;
}

void lowerString(char *s1)
{
	int i = 0;
	for (i = 0; *(s1 + i); i++){
		*(s1 + i) = tolower(*(s1 + i));
	}
}

void printResults(const int *total)
{
	int i = 0;
	
	printf("Lower case and upper case letters count together.\n");
	for (i = 0; i < ALPHABET_SIZE; i++){
		printf("%c\t= %d %s\n", (START_CHAR_LOWER + i), total[i], "times.");
	}
}
