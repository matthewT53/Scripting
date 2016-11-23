/* 
	Author: Matthew Ta
	Date: 1/7/2015
	Description: Program to tokenize a phone number
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LENGTH 15
#define DELIMITER1 " "
#define DELIMITER2 "-"
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define NULL_CHAR '\0'

int main(void)
{
	int areaCode = 0;
	long int phoneNum = 0;
	char phoneNumber[MAX_LENGTH], *ptr_phoneNum = NULL, *word_token = NULL;
	char *openingBracket = NULL, *closingBracket = NULL;
	char *s1 = NULL, *s2 = NULL;
	
	// input the phone number
	printf("Enter a phone number: \n");
	ptr_phoneNum = fgets(phoneNumber, MAX_LENGTH, stdin);
	
	// get the area code as a token
	word_token = strtok(ptr_phoneNum, DELIMITER1);

	// check for the brackets and then remove the brackets
	openingBracket = strchr(word_token, OPEN_BRACKET);
	assert(openingBracket != NULL);
	word_token++;
	closingBracket = strchr(word_token, CLOSE_BRACKET);
	assert(closingBracket != NULL);
	*closingBracket = NULL_CHAR;
	
	// convert area code to an int type
	areaCode = atoi(word_token);

	// now extract the remaining 7 digits
	word_token = strtok(NULL, DELIMITER1);	
	s1 = strtok(word_token, DELIMITER2);
	s2 = strtok(NULL, DELIMITER2);
	strcat(s1, s2);
	phoneNum = atol(s1);
	
	printf("Area code: %d and Phone Number: %ld.\n", areaCode, phoneNum);
	return 0;
}
