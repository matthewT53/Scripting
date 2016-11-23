/*
	Author: Matthew Ta
	Date: 5/7/2015
	Description: Implementations of the functions from myStrings.h
*/

#include <stdio.h>
#include <assert.h>
#include "myStrings.h"

// constant for some of the functions
#define ASCII_ZERO '0'
#define LAST_ASCII_DIGIT '9'
#define DECIMAL_POINT '.'
#define MINUS_SIGN '-'
#define NEGATIVE -1
#define BASE_TEN 10
#define MAX_DIGIT 9
#define FIRST_CHAR_LOWER 97
#define FIRST_CHAR_UPPER 65
#define ALPHABET_SIZE 26

// character constants
#define NULL_CHAR '\0'

// boolean constants
#define TRUE 1
#define FALSE 0

// constants for number bases
#define MIN_BASE 2
#define MAX_BASE 32
#define DEFAULT 0

#define DIFFERENCE_LOWER 87
#define DIFFERENCE_UPPER 55

#define DIGIT 1
#define UPPER_LETTER 2
#define LOWER_LETTER 3

// standard input/output function constants
#define SIZE_CHAR 2

// string comparison constants
#define STR1_LESS_THAN_STR2 -1
#define STR2_LESS_THAN_STR1 1

/*
	Notes:
	* Need to make sure that the string sent to these functions does not point to NULL
*/

int char_digit_letter(const int, const int);

double stof(const char *str)
{
	int negative = FALSE, i = 0, startIndex = 0;
	double value = 0, multiplier = 0;
	// determine if the number is negative
	if (*str == MINUS_SIGN){
		startIndex  = 1;
		negative = TRUE;
	}

	// find the maximum place value
	i = startIndex;
	multiplier = 1;
	while (*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT){
		multiplier *= BASE_TEN;
		i++;
	}
	
	// construct the floating point number
	i = startIndex;
	while ((*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT) || *(str + i) == DECIMAL_POINT){
		if (*(str + i) != DECIMAL_POINT){
			multiplier /= BASE_TEN;
			value += (*(str + i) - ASCII_ZERO) * multiplier;
		}

		i++;
	}
	
	// if the value is negative muliply it by -1
	if (negative == TRUE){
		value *= NEGATIVE;
	}
	
	return value;
}

int stoi(const char *str)
{
	int value = 0, negative = FALSE, i = 0, multiplier = 0, numDigits = 0, startIndex = 0;

	// determine if the number is negative
	if (*str == MINUS_SIGN){
		negative = TRUE;
		startIndex = 1;
	}

	// find the maximum place value
	multiplier = 1;
	i = startIndex;
	while (*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT){
		multiplier *= BASE_TEN;
		i++;
	}

	numDigits = i;
	
	// construct the number
	for (i = startIndex; i < numDigits; i++){
		multiplier /= BASE_TEN;
		value += (*(str + i) - ASCII_ZERO) * multiplier;
	}

	// add the negative sign if the number is negative
	if (negative == TRUE){
		value = value * NEGATIVE;
	}

	// printf("(DEBUG): %d.\n", value);	
	
	return value;
}

long stol(const char *str)
{
	long value = 0, i = 0, multiplier = 0, numDigits = 0;
	int  negative = FALSE, startIndex = 0;
	// determine if the number is negative
	if (*str == MINUS_SIGN){
		negative = TRUE;
		startIndex = 1;
	}

	// find the maximum place value
	multiplier = 1;
	i = startIndex;
	while (*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT){
		multiplier *= BASE_TEN;
		i++;
	}

	numDigits = i;
	
	// construct the number
	for (i = startIndex; i < numDigits; i++){
		multiplier /= BASE_TEN;
		value += (*(str + i) - ASCII_ZERO) * multiplier;
	}

	// add the negative sign if the number is negative
	if (negative == TRUE){
		value = value * NEGATIVE;
	}

	// printf("(DEBUG): %ld.\n", value);	
	
	return value;
}

double stofre(const char *str, char **remainderPtr)
{
	int negative = FALSE, i = 0, startIndex = 0;
	double value = 0, multiplier = 0;
	// determine if the number is negative
	if (*str == MINUS_SIGN){
		startIndex  = 1;
		negative = TRUE;
	}

	// find the maximum place value
	i = startIndex;
	multiplier = 1;
	while (*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT){
		multiplier *= BASE_TEN;
		i++;
	}
	
	// construct the floating point number
	i = startIndex;
	while ((*(str + i) - ASCII_ZERO >= 0 && *(str + i) - ASCII_ZERO <= MAX_DIGIT) || *(str + i) == DECIMAL_POINT){
		if (*(str + i) != DECIMAL_POINT){
			multiplier /= BASE_TEN;
			value += (*(str + i) - ASCII_ZERO) * multiplier;
		}

		i++;
	}

	// assign the remainderPtr the string after the double value
	*remainderPtr = (char *) (str + i);
	if (**remainderPtr == 0){
		*remainderPtr = NULL;
	}
	
	// if the value is negative muliply it by -1
	if (negative == TRUE){
		value *= NEGATIVE;
	}

	// printf("(DEBUG) value = %.5f\n", value);

	return value;
}

long stolre(const char *str, char **remainderPtr, unsigned int base)
{
	int negative = FALSE, startIndex = 0, i = 0, validChar = 0;
	long maxPower = 0, value = 0;
	// check if base is valid
	assert(base == 0 || (base >= MIN_BASE && base <= MAX_BASE));
	if (base == 0){
		base = BASE_TEN;
	}

	// determine if the number is negative
	if (*str == MINUS_SIGN){
		negative = TRUE;
		startIndex = 1;
	}

	// find the highest power to use
	i = startIndex;
	maxPower = 1;
	validChar = TRUE;
	while (*(str + i) != NULL_CHAR && validChar != FALSE){
		validChar = char_digit_letter(*(str + i), base);
		if (validChar != FALSE){
			maxPower *= base;
		}
		
		i++;
	}

	// construct the long number
	i = startIndex;
	validChar = TRUE;
	while (*(str + i) != NULL_CHAR && validChar != FALSE){
		maxPower /= base;
		// determine the correct value to use based on the number system specified
		validChar = char_digit_letter(*(str + i), base);
		if (validChar != FALSE){
			if (validChar == DIGIT){
				value += (*(str + i) - ASCII_ZERO) * maxPower;
			}

			if (validChar == UPPER_LETTER){
				value += (*(str + i) - DIFFERENCE_UPPER) * maxPower;
			}

			if (validChar == LOWER_LETTER){
				value += (*(str + i) - DIFFERENCE_LOWER) * maxPower;
			}
		}

		i++;
	}
	
	*remainderPtr = (char *) (str + i);
	if (**remainderPtr == 0){
		*remainderPtr = NULL;
	}

	// if the number is negative make the result negative
	if (negative == TRUE){
		value *= NEGATIVE;
	}

	return value;
}

unsigned long stoulre(const char *str, char **remainderPtr, unsigned int base)
{
	int negative = FALSE, startIndex = 0, i = 0, validChar = 0;
	unsigned long maxPower = 0, value = 0;
	// check if base is valid
	assert(base == 0 || (base >= MIN_BASE && base <= MAX_BASE));
	if (base == 0){
		base = BASE_TEN;
	}

	// determine if the number is negative
	if (*str == MINUS_SIGN){
		negative = TRUE;
		startIndex = 1;
	}

	// find the highest power to use
	i = startIndex;
	maxPower = 1;
	validChar = TRUE;
	while (*(str + i) != NULL_CHAR && validChar != FALSE){
		validChar = char_digit_letter(*(str + i), base);
		if (validChar != FALSE){
			maxPower *= base;
		}
		i++;
	}

	// construct the long number
	i = startIndex;
	validChar = TRUE;
	while (*(str + i) != NULL_CHAR && validChar != FALSE){
		maxPower /= base;
		// determine the correct value to use based on the number system specified
		validChar = char_digit_letter(*(str + i), base);
		if (validChar != FALSE){
			if (validChar == DIGIT){
				value += (*(str + i) - ASCII_ZERO) * maxPower;
			}

			if (validChar == UPPER_LETTER){
				value += (*(str + i) - DIFFERENCE_UPPER) * maxPower;
			}

			if (validChar == LOWER_LETTER){
				value += (*(str + i) - DIFFERENCE_LOWER) * maxPower;
			}
		}

		i++;
	}
	
	*remainderPtr = (char *) (str + i);
	if (**remainderPtr == 0){
		*remainderPtr = NULL;
	}

	// if the number is negative make the result negative
	if (negative == TRUE){
		value *= NEGATIVE;
	}
	
	// printf("(DEBUG) value = %lu.\n", value);
	return value;
}

int char_digit_letter(const int c, const int num_sys)
{
	int returnValue = FALSE;

	if (c - ASCII_ZERO >= 0 && c - ASCII_ZERO <= MAX_DIGIT){
		returnValue = TRUE;
	}

	else if (c - FIRST_CHAR_UPPER >= 0 && c - FIRST_CHAR_UPPER <= ALPHABET_SIZE){
		if (c - DIFFERENCE_UPPER < num_sys){
			returnValue = 2;
		}
	}

	else if (c - FIRST_CHAR_LOWER >= 0 && c - FIRST_CHAR_LOWER <= ALPHABET_SIZE){
		if (c - DIFFERENCE_LOWER < num_sys){
			returnValue = 3;
		}
	}

	else{
		returnValue = FALSE;
	}


	return returnValue;
}

// functions for copying and concatenation

// array subscripting
char *scpy(char *str1, const char *str2)
{
	int i = 0;
	char *returnPtr = NULL;

	for (i = 0; *(str2 + i) != NULL_CHAR; i++){
		*(str1 + i) = *(str2 + i);
	}
	
	*(str1 + i) = NULL_CHAR;
	
	returnPtr = str1;
	return returnPtr;
}

char *sncpy(char *str1, const char *str2, const unsigned int bytes)
{
	int i = 0;
	char *returnPtr = NULL;

	for (i = 0; *(str2 + i) != NULL_CHAR && i < (int) bytes; i++){
		*(str1 + i) = *(str2 + i);
	}

	*(str1 + i) = NULL_CHAR;
	
	returnPtr = str1;
	return returnPtr;
}

// using pointer arithmetic
char *scpyPtr(char *str1, const char *str2)
{
	char *returnPtr = str1;

	for (; *str2 != NULL_CHAR; *str1 = *str2, str1++, str2++);
	*str1 = NULL_CHAR;
	
	return returnPtr;
}

char *sncpyPtr(char *str1, const char *str2, const unsigned int bytes)
{
	int i = 0;
	char *returnPtr = str1;
	
	for (i = 0; *str2 != NULL_CHAR && i < (int) bytes; *str1 = *str2, str1++, str2++, i++);
	*str1 = NULL_CHAR;

	return returnPtr;
}

char *scat(char *str1, const char *str2)
{
	int i = 0, j = 0;
	char *returnPtr = NULL;
	// locate the null char of the first string
	while (*(str1 + i) != NULL_CHAR){
		i++;
	}

	// overwrite this with the second string
	while (*(str2 + j) != NULL_CHAR){
		*(str1 + i) = *(str2 + j);
		i++;
		j++;
	}
	
	*(str1 + i) = NULL_CHAR;
	
	returnPtr = str1;
	return returnPtr;
}

char *sncat(char *str1, const char *str2, const unsigned int bytes)
{
	char *returnPtr = NULL;
	int i = 0, j = 0;
	
	// locate the null char in the first string
	while (*(str1 + i) != NULL_CHAR){
		i++;
	}

	// join a certain number of bytes from the second string to the first string
	while (*(str2 + j) != NULL_CHAR && j < (int) bytes){
		*(str1 + i) = *(str2 + j);
		j++;
		i++;
	}
	
	*(str1 + i) = NULL_CHAR;
	returnPtr = str1;
	return returnPtr;
}

char *scatPtr(char *str1, const char *str2)
{
	char *returnPtr = str1;

	// locate the null char of the first string
	while (*str1 != NULL_CHAR){
		str1++;
	}

	// join the second string with the first string
	while (*str2 != NULL_CHAR){
		*str1 = *str2;
		str2++;
		str1++;
	}

	*str1 = NULL_CHAR;

	return returnPtr;
}

char *sncatPtr(char *str1, const char *str2, const unsigned int bytes)
{
	char *returnPtr = str1;
	int i = 0;

	// find the null char of the first str
	while (*str1 != NULL_CHAR){
		str1++;
	}

	// join a certain number of bytes from the second string to the first string
	while (*str2 != NULL_CHAR && i < (int) bytes){
		*str1 = *str2;
		str1++;
		str2++;
		i++;
	}

	*str1 = NULL_CHAR;

	return returnPtr;
}

int inchr(void)
{
	char *strPtr = NULL;
	char chrArray[SIZE_CHAR];
	int chr = 0;

	// need room for the null char
	strPtr = fgets(chrArray, SIZE_CHAR, stdin);
	if (strPtr == NULL){
		printf("Error when trying to read character.\n");
	}

	chr = chrArray[0];
	return chr;	
}

int outchr(int c)
{
	printf("%c", c);
	return c;
}

int outstr(const char *str)
{
	int chrsPrinted = 0, returnValue = 0;
	if (str != NULL){
		while (*str != NULL_CHAR){
			printf("%c", *str);
			str++;
			chrsPrinted++;
		}

		printf("\n"); 
		returnValue = chrsPrinted;
	}

	else{
		returnValue = -1;
	}

	return returnValue;
}

int scmp(const char *str1, const char *str2)
{
	int returnValue = 0, determinedResult = FALSE;
	int i = 0;

	for (i = 0; *(str1 + i) != NULL_CHAR && *(str2 + i) != NULL_CHAR && determinedResult != TRUE; i++){
		if (*(str1 + i) > *(str2 + i)){
			returnValue = STR2_LESS_THAN_STR1;
			determinedResult = TRUE;
		}

		if (*(str1 + i) < *(str2 + i)){
			returnValue = STR1_LESS_THAN_STR2;
			determinedResult = TRUE;
		}
	}

	if (*(str1 + i) == NULL_CHAR && *(str2 + i) != NULL_CHAR){
		returnValue = STR1_LESS_THAN_STR2;
	}

	if (*(str1 + i) != NULL_CHAR && *(str2 + i) == NULL_CHAR){
		returnValue = STR2_LESS_THAN_STR1;
	}
	
	printf("(DEBUG): retValue = %d.\n", returnValue);
	return returnValue;

}

int sncmp(const char *str1, const char *str2, const unsigned int n)
{
	int returnValue = 0, determinedResult = FALSE;
	int i = 0;
	
	for (i = 0; *(str1 + i) != NULL_CHAR && *(str2 + i) != NULL_CHAR && determinedResult != TRUE && i < (int) n; i++){
		if (*(str1 + i) > *(str2 + i)){
			returnValue = STR2_LESS_THAN_STR1 * i;
			determinedResult = TRUE;
		} 

		if (*(str1 + i) < *(str2 + i)){
			returnValue = STR1_LESS_THAN_STR2 * i;
			determinedResult = TRUE;
		}
	}
		
	if (*(str1 + i) != NULL_CHAR && *(str2 + i) == NULL_CHAR){
		if (i == 0){
			i = 1;
		}
		returnValue = STR2_LESS_THAN_STR1 * i;
	}

	if (*(str1 + i) == NULL_CHAR && *(str2 + i) != NULL_CHAR){
		if (i == 0){
			i = 1;
		}
		returnValue = STR1_LESS_THAN_STR2 * i;
	}

	printf("(DEBUG): retValue = %d.\n", returnValue);
	return returnValue;
} 

int scmpPtr(const char *str1, const char *str2)
{
	int returnValue = 0, exitLoop = FALSE;

	for (; *str1 != NULL_CHAR && *str2 != NULL_CHAR && exitLoop != TRUE; str1++, str2++){
		if (*str1 > *str2){
			returnValue = STR2_LESS_THAN_STR1;
			exitLoop = TRUE;
		}

		if (*str1 < *str2){
			returnValue = STR1_LESS_THAN_STR2;
			exitLoop = TRUE;
		}
	}

	if (*str1 == NULL_CHAR && *str2 != NULL_CHAR){
		returnValue = STR1_LESS_THAN_STR2;
	}

	if (*str1 != NULL_CHAR && *str2 == NULL_CHAR){
		returnValue = STR2_LESS_THAN_STR1;
	}
	
	printf("(DEBUG): retValue = %d.\n", returnValue);
	return returnValue;
}

int sncmpPtr(const char *str1, const char *str2, const unsigned int n)
{
	int returnValue = 0, exitLoop = FALSE;
	int i = 0;
	
	for (i = 0; *str1 != NULL_CHAR && *str2 != NULL_CHAR && exitLoop != TRUE && i < (int) n; str1++, str2++, i++){
		if (*str1 > *str2){
			returnValue = STR2_LESS_THAN_STR1 * i;
			exitLoop = TRUE;
		}

		if (*str1 < *str2){
			returnValue = STR1_LESS_THAN_STR2 * i;
			exitLoop = TRUE;
		}
	}

	// if no comparisons were made set i as 1 to prevent multiplication by zero
	if (i == 0){
		i = 1;
	}
	
	if (*str1 != NULL_CHAR && *str2 == NULL_CHAR){
		returnValue = STR2_LESS_THAN_STR1 * i;
	}

	if (*str1 == NULL_CHAR && *str2 != NULL_CHAR){
		returnValue = STR1_LESS_THAN_STR2 * i;
	}
	
	printf("(DEBUG): retValue = %d.\n", returnValue);
	return returnValue;
}

char *cfstr(const char *str, const char c)
{
	int foundChar = FALSE;
	char *returnPtr = NULL;
	
	while (*str != NULL_CHAR && foundChar != TRUE){
		if (*str == c){
			foundChar = TRUE;
			returnPtr = (char *) str;
		}

		str++;
	}

	if (c == NULL_CHAR){
		returnPtr = (char *) str;
	}

	return returnPtr;
}

unsigned int strsegnot(const char *str1, const char *str2)
{
	unsigned int exclusiveChars = 0; 
	int foundChar = FALSE;
	int i = 0, j = 0;

	for (i = 0; *(str1 + i) != NULL_CHAR && foundChar != TRUE; i++){
		foundChar = FALSE;
		for (j = 0; *(str2 + j) != NULL_CHAR && foundChar != TRUE; j++){
			if (*(str1 + i) == *(str2 + j)){
				foundChar = TRUE;
			}
		}

		if (foundChar != TRUE){
			exclusiveChars++;
		}
	}

	return exclusiveChars;
}

unsigned int strsegin(const char *str1, const char *str2)
{
	unsigned int inclusiveChars = 0; 
	int foundChar = TRUE;
	int i = 0, j = 0;

	for (i = 0; *(str1 + i) != NULL_CHAR && foundChar != FALSE; i++){
		foundChar = FALSE;
		for (j = 0; *(str2 + j) != NULL_CHAR && foundChar != TRUE; j++){
			if (*(str1 + i) == *(str2 + j)){
				foundChar = TRUE;
			}
		}

		if (foundChar == TRUE){
			inclusiveChars++;
		}
	}
	
	return inclusiveChars;
}

char *strc(const char *str1, const char *str2)
{
	int sameChar = FALSE;
	int i = 0, j = 0;
	char *returnPtr = NULL;
	
	while (*(str1 + i) != NULL_CHAR && sameChar != TRUE){
		j = 0;
		while (*(str2 + j) != NULL_CHAR && sameChar != TRUE){
			if (*(str1 + i) == *(str2 + j)){
				sameChar = TRUE;
				returnPtr = (char *) (str1 + i);
			}
			j++;
		}
		
		i++;
	}

	return returnPtr;
}

char *clstr(const char *str, const char c)
{
	int length = 0, i = 0;
	int foundChar = FALSE;
	char *returnPtr = NULL;

	while (*str != NULL_CHAR){
		str++;
		length++;
	}

	for (i = length; i >= 0 && foundChar != TRUE; i--){
		if (*(str + i) == c){
			foundChar = TRUE;
			returnPtr = (char *) (str + i);
		}
	}

	return returnPtr;
}

char *strinstr(const char *str1, const char *str2)
{
	int i = 0, j = 0, c = 0;
	int chrNotEqual = FALSE;
	char *returnPtr = NULL;

	while (*(str1 + i) != NULL_CHAR && returnPtr == NULL){
		j = 0;
		chrNotEqual = FALSE;
		c = i;
		while (*(str2 + j) != NULL_CHAR && *(str1 + c) != NULL_CHAR){
			if (*(str1 + c) != *(str2 + j)){
				chrNotEqual = TRUE;
			}
			
			c++;
			j++; 
		}

		if (chrNotEqual == FALSE && *(str2 + j) == NULL_CHAR){
			returnPtr = (char *) (str1 + i);
		}

		i++;
	}
	
	return returnPtr;
}

// finds last occurence of string in a string
char *strinstrl(const char *str1, const char *str2)
{
	int i = 0, j = 0, c = 0;
	int chrNotEqual = FALSE;
	char *returnPtr = NULL;

	i = (int) (slength(str1) - slength(str2);
	while (i >= 0 && returnPtr == NULL){
		j = 0;
		chrNotEqual = FALSE;
		c = i;
		while (*(str2 + j) != NULL_CHAR && *(str1 + c) != NULL_CHAR){
			if (*(str1 + c) != *(str2 + j)){
				chrNotEqual = TRUE;
			}
			
			c++;
			j++; 
		}

		if (chrNotEqual == FALSE && *(str2 + j) == NULL_CHAR){
			returnPtr = (char *) (str1 + i);
		}

		i--;
	}
	
	return returnPtr;
}

/*
	Notes:
	* useful for manipulating file buffers were NULL chars may be in the middle of the buffer
	* allows processing of 'n' bytes of the buffer
*/

char *nstrinstr(const char *str1, const char *str2, const unsigned int maxBytes)
{
	int i = 0, j = 0, c = 0;
	int chrNotEqual = FALSE;
	char *returnPtr = NULL;

	while (i < (int) maxBytes && returnPtr == NULL){
		j = 0;
		chrNotEqual = FALSE;
		c = i;
		while (*(str2 + j) != NULL_CHAR && c < (int) maxBytes){
			if (*(str1 + c) != *(str2 + j)){
				chrNotEqual = TRUE;
			}
			
			c++;
			j++; 
		}

		if (chrNotEqual == FALSE && *(str2 + j) == NULL_CHAR){
			returnPtr = (char *) (str1 + i);
		}

		i++;
	}
	
	return returnPtr;
}

// finds last occurence of string in a string
char *nstrinstrl(const char *str1, const char *str2, const unsigned int maxBytes)
{
	int i = 0, j = 0, c = 0;
	int chrNotEqual = FALSE;
	char *returnPtr = NULL;

	i = maxBytes - (int) (slength(str2));
	while (i >= 0 && returnPtr == NULL){
		j = 0;
		chrNotEqual = FALSE;
		c = i;
		while (*(str2 + j) != NULL_CHAR && c < (int) maxBytes){
			if (*(str1 + c) != *(str2 + j)){
				chrNotEqual = TRUE;
			}
			
			c++;
			j++; 
		}

		if (chrNotEqual == FALSE && *(str2 + j) == NULL_CHAR){
			returnPtr = (char *) (str1 + i);
		}

		i--;
	}
	
	return returnPtr;
}

char *strtokens(char *str, const char *delimiter)
{
	static char *strPtr = NULL;
	char *returnPtr = NULL;
	int exitLoop = FALSE;
	
	// do this only when a string is passed into the function
	if (str != NULL){
		strPtr = str;	
	}
	
	// check if we have reached the end of the string
	if (*strPtr == NULL_CHAR){
		strPtr = NULL;
	}
	
	returnPtr = strPtr;
	// prevent dereferencing a pointer to NULL
	if (strPtr != NULL){
		while (*strPtr != NULL_CHAR && exitLoop != TRUE){
			if (*strPtr == *delimiter){
				*strPtr = NULL_CHAR;
				exitLoop = TRUE;
			}
			
			strPtr++;
		}
	}

	return returnPtr;
}

unsigned int slength(const char *str)
{
	unsigned int length = 0;
	int i = 0;

	// check if the string str is null
	if (str == NULL){
		printf("Error: argument is a pointer to NULL.\n");
		length = -1;
	}

	else{
		for (i = 0; *(str + i) != NULL_CHAR; i++){
			length++;
		}
	}

	return length;
}

unsigned int slengthPtr(const char *str)
{
	unsigned int length = 0;
	
	// check if str points to null
	if (str == NULL){
		printf("Error: argument is a pointer to NULL.\n");
		length = -1;
	}

	else{
		while (*str != NULL_CHAR){
			length++;
			str++;
		}
	}

	return length;
}


