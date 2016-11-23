#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define EQUAL 0
#define SIZE 100

int main(void){
	int cmpValue = 0;
	int objectsRead = 0;
	int numberChars = 0;
	char s1[SIZE], s2[SIZE];

	printf("Enter two strings: \n");
	objectsRead = scanf("%s%s", s1, s2);
	printf("(DEBUG) Objects read = %d.\n", objectsRead);
	printf("Enter number of chars to compare: \n");	
	objectsRead = scanf("%d", &numberChars);
	numberChars = (size_t) numberChars;
	cmpValue = strncmp(s1, s2, numberChars);

	if (cmpValue > EQUAL){
		printf("String 1 is greater than string 2.\n");
	}

	else if (cmpValue < EQUAL){
		printf("String 1 is less then string 2.\n");
	}

	else{
		printf("Both strings are equal.\n");
	}

	return 0;
}
