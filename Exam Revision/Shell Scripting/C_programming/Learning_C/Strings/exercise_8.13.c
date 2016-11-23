/*
	Author: Matthew Ta
	Date: 1/7/2015
	Description: Converts a phrase into pig latin
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define PHRASE_SIZE 100
#define DELIMITER " "
#define TRUE 1
#define FALSE 0

#define SPACE ' '
#define NEWLINE '\n'
#define NULL_CHAR '\0'

void printLatinWord(char *token);
void testLatinWord(void);

int main(void)
{
	char phrase[PHRASE_SIZE];
	char *phrase_ptr = NULL;
	char *word_token = NULL;

	printf("Enter a phrase to be encoded:\n");
	phrase_ptr = fgets(phrase, PHRASE_SIZE, stdin);
	
	word_token = strtok(phrase_ptr, DELIMITER);
	printLatinWord(word_token);

	while ((word_token = strtok(NULL, DELIMITER)) != NULL){
		printLatinWord(word_token);
	}

	return 0;
}

void printLatinWord(char *token)
{
	int length = 0;
	char string[PHRASE_SIZE];
	char first_char, last_char; 
	char *newLineChar = NULL;
	const char *pig_letters = "ay";

	first_char = *token;
	token++;
	strcpy(string, token);
	last_char = SPACE;
	// remove the newline character fron last word
	if ((newLineChar = strchr(string, NEWLINE)) != NULL){
		*newLineChar = NULL_CHAR;
		last_char = NEWLINE;
	}
	
	length = strlen(string);
	string[length] = first_char;
	// get the final string length
	strcat(string, pig_letters);
	length = strlen(string);
	string[length] = last_char;
	string[length + 1] = NULL_CHAR;
	
	printf("%s", string);
	
}

void testLatinWord(void)
{
	char *string = "hello";
	printLatinWord(string);

	char *string2 = "computer";
	printLatinWord(string2);
	
	char *string3 = "the";
	printLatinWord(string3);

}
