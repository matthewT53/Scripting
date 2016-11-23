/*
	Name: Matthew Ta
	Date: 1/8/2015
	Description: Analysis of text
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "miscStrs.h"

#define MAX_LENGTH 250
#define MAX_CHARS 1000
#define NULL_CHAR 0
#define NEWLINE '\n'
#define SPACE 32
#define FIRST_CHAR_LOWER 'a'
#define LAST_CHAR_LOWER 'z'
#define ALPHABET_SIZE 26

// part (b) constants
#define TOKEN " "

// part (a)
void occurencesOfLetters(int *results);
void printResults(const int *results);

// part (b) 
unsigned int numberOfLetters(int *results);
void printResults2(const int *results, const int max);

// part (c)
void numberOfWords(void);

// version 2
void numberOfWords2(void);
void printResults3(const char **words, const int *results);
void sortWords(char **words, int *results); 

int main(void)
{
	// int results[MAX_LENGTH] = {0};
	
	// occurencesOfLetters(results);
	// printResults(results);

	// int maxLength = numberOfLetters(results);
	// printResults2(results, maxLength);
	
	numberOfWords2();

	return EXIT_SUCCESS;
}

void occurencesOfLetters(int *results)
{
	char input[MAX_LENGTH], *strPtr = NULL;
	
	// clear the array in case the caller forgot to
	memset(results, 0, ALPHABET_SIZE);

	// read the lines of text
	strPtr = fgets(input, MAX_LENGTH, stdin);
	removeNewLine(strPtr);

	while (strPtr != NULL){
		 while (*strPtr != NULL_CHAR){
			if ((*strPtr = tolower(*strPtr)) != NULL_CHAR){
				if (*strPtr >= FIRST_CHAR_LOWER && *strPtr <= LAST_CHAR_LOWER){
					results[*strPtr - FIRST_CHAR_LOWER]++;
				}
			}

			strPtr++;
		}
		
		strPtr = NULL;
		memset(input, 0, MAX_LENGTH);
		strPtr = fgets(input, MAX_LENGTH, stdin);
		removeNewLine(strPtr);
	}

}

void printResults(const int *results)
{
	for (int i = 0; i < ALPHABET_SIZE; i++){
		printf("Letter %c appeared %d times.\n", FIRST_CHAR_LOWER + i, *(results + i));
	}
}

unsigned int numberOfLetters(int *results)
{
	char line[MAX_LENGTH], *linePtr = NULL, *tokenStr = NULL;
	unsigned int longestWord = 0, length = 0;
	
	// clear the array just in case the caller didn't clear it
	memset(results, 0, MAX_LENGTH);

	// start reading and analysing
	linePtr = fgets(line, MAX_LENGTH, stdin);
	removeNewLine(linePtr);
	
	while (linePtr != NULL){
		// tokenize the line
		tokenStr = strtok(linePtr, TOKEN);
		while (tokenStr != NULL){
			// do the analysis stuff
			length = strlen(tokenStr);
			if (length > longestWord && length <= MAX_LENGTH){
				longestWord = length;
			}
			
			results[length - 1]++;
			tokenStr = strtok(NULL, TOKEN);
		}

		// read another line
		memset(line, 0, MAX_LENGTH);
		linePtr = fgets(line, MAX_LENGTH, stdin);
		removeNewLine(linePtr);
	}

	return longestWord;
}

void printResults2(const int *results, const int max)
{
	for (int i = 0; i < max; i++){
		printf("Length %d appeared %d times.\n", i + 1, results[i]);
	}
}


// not fully correct if to comes before today, today is not included in results
void numberOfWords(void)
{
	char lines[MAX_CHARS], linesCopy[MAX_CHARS];
	char *strPtr = NULL, *sameStr = NULL;
	int c = 0, i = 0, sameStrCount = 0;

	// clear the array
	memset(lines, 0, MAX_CHARS);
	
	// read in the lines
	while ((c = getchar()) != EOF && i < MAX_CHARS){
		if (c == NEWLINE){
			c = SPACE;
		}
		
		// store the char in the array
		lines[i] = c;
		i++;
	}

	// do the analysis

	// need to make a copy of lines before strtok is called
	strcpy(linesCopy, lines);
	strPtr = strtok(lines, TOKEN);

	while (strPtr != NULL){
		sameStrCount = 0;
		sameStr = strstr(linesCopy, strPtr);
		// if sameStr == NULL then either the word doesnt reside in linesCopy (unlikely) or the word was already counted
		if (sameStr != NULL){
			while (sameStr != NULL){
				sameStrCount++;
				sameStr = strstr(sameStr + 1, strPtr);
			}

			// remove duplicates
			removeDuplicates(linesCopy, strPtr);

			printf("%s appeared %d times.\n", strPtr, sameStrCount);
		}

		strPtr = strtok(NULL, TOKEN);
	}
}

void numberOfWords2(void)
{
	char lines[MAX_CHARS], linesCopy[MAX_CHARS];
	char *strPtr = NULL, *sameStr = NULL;
	char *words[MAX_CHARS] = {NULL};
	int results[MAX_CHARS] = {0};
	int c = 0, i = 0, sameStrCount = 0, ptrCounter = 0;

	// clear the array
	memset(lines, 0, MAX_CHARS);
	
	// read in the lines
	while ((c = getchar()) != EOF && i < MAX_CHARS){
		if (c == NEWLINE){
			c = SPACE;
		}
		
		// store the char in the array
		lines[i] = c;
		i++;
	}

	// do the analysis

	// need to make a copy of lines before strtok is called
	strcpy(linesCopy, lines);
	strPtr = strtok(lines, TOKEN);

	while (strPtr != NULL){
		sameStrCount = 0;
		sameStr = strstr(linesCopy, strPtr);
		// if sameStr == NULL then either the word doesnt reside in linesCopy (unlikely) or the word was already counted
		if (sameStr != NULL){
			while (sameStr != NULL){
				sameStrCount++;
				sameStr = strstr(sameStr + 1, strPtr);
			}

			// remove duplicates
			removeDuplicates(linesCopy, strPtr);
			words[ptrCounter] = strPtr;
			results[ptrCounter] = sameStrCount;
			ptrCounter++;
		}

		strPtr = strtok(NULL, TOKEN);
	}

	// sort the words
	sortWords(words, results);

	// print the results
	printResults3((const char **) words, results);
}

void sortWords(char **words, int *results)
{
	char *tempStr = NULL;
	int i = 0, j = 0, numberWords = 0, temp = 0;

	// find the number of words we have to work with
	for (i = 0; words[i] != NULL; i++){
		numberWords++;
	}

	// do a bubble sort
	for (i = 0; i < numberWords; i++){
		for (j = 0; j < numberWords - 1; j++){
			if (strcmp(words[j], words[j + 1]) > 0){
				// swap the strings
				tempStr = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tempStr;

				// now swap the ints
				temp = results[j];
				results[j] = results[j + 1];
				results[j + 1] = temp;
				
			}
		}

	}
}

void printResults3(const char **words, const int *results)
{
	int i = 0;
	while (words[i] != NULL){
		printf("%s appeared %d times.\n", words[i], results[i]);
		i++;
	}
}

