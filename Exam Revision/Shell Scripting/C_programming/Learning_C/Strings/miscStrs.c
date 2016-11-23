/*
	Name: Matthew Ta
	Date: 1/8/2015
	Description: Contains implementations of the function prototypes in the corresonding header file
*/

// #include <stdio.h>
#include <string.h>

#include "miscStrs.h"

#define NULL_CHAR 0
#define NEW_LINE '\n'
#define SPACE 32

/*
 * Only for testing, remove to compile with other programs
int main(void)
{
	char array[100] = "sdgdgs asjkfkjsnfkj to to fsdfs to", *word = "to";
		
	removeDuplicates(array, word, 100);
	return 0;
}
*/

char *removeNewLine(char *str)
{
	char *retPtr = NULL;
	char *newLine = NULL;
	
	if (str != NULL){
		newLine = strchr(str, NEW_LINE);
		if (newLine != NULL){
			*newLine = NULL_CHAR;
			retPtr = str;
		}
	}

	return retPtr;
}

// note strToRemove must be a pointer that is part of them memory range 
char *removeDuplicates(char *str, const char *strToRemove)
{
	char *retPtr = NULL;
	char *strPtr = NULL;
	int temp = 0;
	unsigned int i = 0, j = 0, length = 0;
	
	
	// if we are not getting trolled, commence business
	if (str != NULL && strToRemove != NULL){
		// printf("Original: %s\n", str);
		// move the pointer to the second occurence of the str
		strPtr = strstr(str, strToRemove);
		// printf("strPtr = %s.\n", strPtr);

		while (strPtr != NULL){
			i = 0;
			// printf("strlen(strPtr) = %d.\n", (int) strlen(strPtr));
			// possible bug if < not <= then no trailing string is not copied
			// reason: before decl of length we used strlen(strPtr) in the while cond but strPtr was being changed inside the while so wierd stuff happened
			length = strlen(strPtr);
			if(*(strPtr + strlen(strToRemove)) == SPACE){
				while (i < length){
					j = strlen(strToRemove) + i;
					temp = *(strPtr + j);
					*(strPtr + j) = NULL_CHAR;
					*(strPtr + i) = temp;
					// printf("set stuff.\n");
					i++;
				}
			}
				
			// printf("str = %s\n", str);
			strPtr = strstr(strPtr + 1, strToRemove);
		}

		// printf("str = %s.\n", str);

		retPtr = str;
	}

	return retPtr;
}
