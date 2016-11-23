/*
	Name: Matthew Ta
	Date: 28/6/2015
	Description: This program performs various tests on the char that the user inputs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void){
	char c;
	int charsRead = 0;
	
	// input a character
	printf("Enter a character: \n");
	charsRead = scanf("%c", &c);
	printf("Chars read into scanf() = %d.\n", charsRead);
	// now commence the testing
	printf("%c %s digit.\n", c, isdigit(c) ? "is a" : "is not a");
	printf("%c %s letter.\n", c, isalpha(c) ? "is a" : "is not a");
	printf("%c %s digit V letter.\n", c, isalnum(c) ? "is a" : "is not a");
	printf("%c %s hex digit or char.\n", c, isxdigit(c) ? "is a" : "is not a");
	printf("%c %s lowercase letter.\n", c, islower(c) ? "is a" : "is not a");
	printf("%c %s uppercase letter.\n", c, isupper(c) ? "is a" : "is not a");
	printf("%c as lowercase letter %c.\n", c, tolower(c));
	printf("%c as uppercase letter %c.\n", c, toupper(c));
	printf("%c %s printing character.\n", c, isspace(c) ? "is a" : "is not a");
	printf("%c %s control char.\n", c, iscntrl(c) ? "is a" : "is not a");
	printf("%c %s punctuation character.\n", c, ispunct(c) ? "is a" : "is not a");
	printf("%c %s printing char including space.\n", c, isprint(c) ? "is a" : "is not a");
	printf("%c %s printing char other than space.\n", c, isgraph(c) ? "is a" : "is not a");
	
	return 0;
}
