/*
	Author: Matthew Ta
	Date: 4/7/2015
	Description: Implementations of the functions from charset.h
*/

#include "charTypes.h"

// ASCII constants
#define LAST_ASCII 127

// digit constants
#define BASE_DIGIT '0'
#define MAX_DIGIT 10

// letter constants
#define ALPHABET_SIZE 26
#define FIRST_CHAR_UPPER 65
#define LAST_CHAR_UPPER 90

#define FIRST_CHAR_LOWER 97
#define LAST_CHAR_LOWER 122

#define UPPER_LOWER_DIFFERENCE 32

// hex constants
#define HEX_LETTER_SIZE 6
#define HEX_FIRST_CHAR_LOWER 97
#define HEX_FIRST_CHAR_UPPER 65

// boolean constants
#define TRUE 1
#define FALSE 0

// formatting characters i.e
#define NEWLINE '\n'
#define SPACE ' '
#define FORM_FEED '\f'
#define CAR_RETURN '\r'
#define HORIZONTAL_TAB '\t'
#define VERTICAL_TAB '\v'

// extra control characters
#define BACKSPACE '\b'
#define SINGLE_QUOTE '\''
#define BACKSLASH '\\'

// null character
#define NULL_CHAR '\0'

int isCharDigit(int c)
{
	int returnValue = FALSE;
	if (c - BASE_DIGIT >= 0 && c - BASE_DIGIT < MAX_DIGIT){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharLetter(int c)
{
	int returnValue = FALSE;

	// determine if c is an upper char or lower char letter
	if ((c - FIRST_CHAR_UPPER >= 0 && c - FIRST_CHAR_UPPER < ALPHABET_SIZE) || (c - FIRST_CHAR_LOWER >= 0 && c - FIRST_CHAR_LOWER < ALPHABET_SIZE)){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharDigNum(int c)
{
	int returnValue = FALSE;
	
	// determine if c is a letter or a digit
	if (c - BASE_DIGIT >= 0 && c - BASE_DIGIT < MAX_DIGIT){
		returnValue = TRUE;
	}

	else if ((c - FIRST_CHAR_UPPER >= 0 && c - FIRST_CHAR_UPPER < ALPHABET_SIZE) || (c - FIRST_CHAR_LOWER >= 0 && c - FIRST_CHAR_LOWER < ALPHABET_SIZE)){
		returnValue = TRUE;
	}

	else{
		returnValue = FALSE;
	}


	return returnValue;
}

int isCharHex(int c)
{
	int returnValue = FALSE;
	
	// determine if c is a hex digit or character
	if (c - BASE_DIGIT >= 0 && c - BASE_DIGIT < MAX_DIGIT){
		returnValue = TRUE;
	}

	else if ((c - HEX_FIRST_CHAR_LOWER >= 0 && c - HEX_FIRST_CHAR_LOWER < HEX_LETTER_SIZE) || (c - HEX_FIRST_CHAR_UPPER >= 0 && c - HEX_FIRST_CHAR_UPPER < HEX_LETTER_SIZE)){
		returnValue = TRUE;
	}

	else{
		returnValue = FALSE;
	}

	return returnValue;
}

int isCharUpper(int c)
{
	int returnValue = FALSE;

	// determine if c is an upper char letter
	if (c - FIRST_CHAR_UPPER >= 0 && c - FIRST_CHAR_UPPER < ALPHABET_SIZE){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharLower(int c)
{
	int returnValue = FALSE;

	// determine if c is a lower char letter
	if (c - FIRST_CHAR_LOWER >= 0 && c - FIRST_CHAR_LOWER < ALPHABET_SIZE){
		returnValue = TRUE;
	}

	return returnValue;
}

int convertToLower(int c)
{
	int returnChar = 0;

	// determine if any changes need to occur
	if (c - FIRST_CHAR_UPPER >= 0 && c - FIRST_CHAR_UPPER < ALPHABET_SIZE){
		returnChar = c + UPPER_LOWER_DIFFERENCE;
	}

	else{
		returnChar = c;
	}

	return returnChar;
}

int convertToUpper(int c)
{
	int returnChar = 0;

	// determine if any changes need to occur
	if (c - FIRST_CHAR_LOWER >= 0 && c - FIRST_CHAR_LOWER < ALPHABET_SIZE){
		returnChar = c - UPPER_LOWER_DIFFERENCE;
	}

	else{
		returnChar = c;
	}

	return returnChar;
}

int isCharFormat(int c)
{
	int returnValue = FALSE;

	if (c == NEWLINE || c == SPACE || c == FORM_FEED || c == CAR_RETURN || c == HORIZONTAL_TAB || c == VERTICAL_TAB){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharControl(int c)
{
	int returnValue = FALSE;
	
	if (c == NEWLINE || c == FORM_FEED || c == BACKSPACE || c == CAR_RETURN || c == HORIZONTAL_TAB || c == VERTICAL_TAB || c == SINGLE_QUOTE || c == BACKSLASH){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharPunct(int c)
{
	int returnValue = FALSE;
	// punctuation characters start at ASCII code 33
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharPrint(int c)
{
	int returnValue = FALSE;

	// every char except control characters
	if (c >= SPACE && c < LAST_ASCII){
		returnValue = TRUE;
	}

	return returnValue;
}

int isCharPrint_space(int c)
{
	int returnValue = FALSE;
	
	// every char except control characters and spaces
	if (c > SPACE && c < LAST_ASCII){
		returnValue = TRUE;
	}

	return returnValue;
}
