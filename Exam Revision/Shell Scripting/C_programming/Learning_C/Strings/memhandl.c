/*
	Name: Matthew Ta
	Date: 14/7/2015
	Description:  This file contains the function definitions for the memory handling functions in the header file.

	References: 
	http://stackoverflow.com/questions/3572309/memmove-implementation-in-c

*/

#include <stdio.h>

// memblkcmp constants
#define MEM1_LESS_MEM2 -1
#define MEM1_GREATER_MEM2 1
#define EQUAL 0

// boolean constants
#define TRUE 1
#define FALSE 0

void *memblkcpy(void *memb1, const void *memb2, const unsigned int numbytes)
{
	void *returnPtr = memb1;
	int i = 0;

	if ((char *) memb2 != NULL && (char *) memb1 != NULL){
		for (i = 0; i < numbytes; i++, memb1++, memb2++){
			*((char *) memb1) = *((char *) memb2);
		}
	}

	else{
		returnPtr = NULL;
	}

	return returnPtr;
}

void *memblkmove(void *memb1, const void *memb2, const unsigned int numbytes)
{
	void *returnPtr = memb1;
	char temp[numbytes];
	int i = 0, copyingDone = FALSE;

	if ((char *) memb1 != NULL && (char *) memb2 != NULL){	
		// determine which direction to copy from to avoid data corruption when dealing with overlaps
		if (memb1 > memb2 || memb1 < memb2){
			// copy the contents of the second argument into the temp array
			for (i = 0; i < numbytes; i++, memb2++){
				temp[i] = *((char *) memb2);
			}

			if (memb1 > memb2){
				// loop memb1 to the end
				i = 0;
				while (i < numbytes){
					memb1++;
					i++;
				}

				// start copying to memb1 from end of memb2
				for (i = numbytes - 1; i >= 0; i--, memb1--){
					*((char *) memb1) = temp[i];
				}

				copyingDone = TRUE;
			}
		
			//possible bug only meant to execute one of these if statements
			if (memb1 < memb2 && copyingDone != TRUE){
				// start copying from beginning of memb2
				for (i = 0; i < numbytes; i++, memb1++){
					*((char *) memb1) = temp[i];
				}

			}
		}
	}

	else{
		returnPtr = NULL;
	}

	return returnPtr;
}

int memblkcmp(const void *memb1, const void *memb2, const unsigned int numbytes)
{
	unsigned int returnValue = EQUAL, i = 0;
	int exitLoop = FALSE;
	
	if ((char *) memb1 != NULL && (char *) memb2 != NULL){	
		for (i = 0; i < numbytes && exitLoop != TRUE; i++){
			if (*((char *) memb1) > *((char *) memb2)){
				returnValue = MEM1_GREATER_MEM2;
				exitLoop = TRUE;	
			}

			if (*((char *) memb1) < *((char *) memb2)){
				returnValue = MEM1_LESS_MEM2;
				exitLoop = TRUE;
			}
		}
	}
		
	return returnValue;
}

void *memblkchr(const void *memb, int byte, const unsigned int numbytes)
{
	void *returnPtr = NULL;
	int exitLoop = FALSE;
	unsigned int i = 0;	
	unsigned char c = byte;
	// printf("c = %c.\n", c);
	
	if ((char *) memb != NULL){
		while (i < numbytes && exitLoop != TRUE){
			if (*((char *) memb) == c){
				returnPtr = (char *) memb;
				exitLoop = TRUE;
			}

			memb++;
			i++;
		}
	}

	else{
		returnPtr = NULL;
	}
	
	return returnPtr;
}

void *memblkset(void *memb, int byte, const unsigned int numbytes)
{
	void *returnPtr = memb;
	unsigned char c = byte;
	int i = 0;

	for (i = 0; i < numbytes; i++, memb++){
		*((char *) memb) = c;
	}

	return returnPtr;
}


