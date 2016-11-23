/*
	Name: Matthew Ta
	Date: 3/8/2015
	Description: Formats blocks of text in type-justification format
*/

/* 
	Logs:
	* made some progress, the line now alligns to the left margin perfectly
	* Still need to remove the trailing spaces, text does not allign to the right margin correctly
	* further progress, text now lines up with both the left and right margins
	* working, just need to make it more efficient
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MARG_SIZE 10 // multiply this with the space char. 10 spaces = 1 inch
#define MAX_CHARS 65 // max chars per line 

// sizes of buffers as constants
#define MAX_OUTPUT 1000
#define MAX_INPUT 500
#define BUFFER_SIZE 80

// character constants
#define NEWLINE '\n'
#define SPACE 32
#define NULL_CHAR 0
#define BLANK " "
#define DELIMITER " "

// boolean constants
#define TRUE 1
#define FALSE 0

// constants for the foramtting pattern
#define PATTERN_LEFT 2
#define PATTERN_RIGHT 1

char *typeJustify(char *desBlock, char *srcBlock);

// copys part of source into des
char *copySections(char *des, const char *src, const unsigned int startPos, const int numberOfChars);

// alligns the text in type-justification, allign the words after removing blanks
char *allignText(char *line, const int blanksToAddFront, const int blanksToAddBack);

// shift the letters up by one position in a char array
char *shiftArrayUp(char *array);

// add the null character after the newline character
char *addNullAfterNl(char *str);

int main(void)
{
	char strInput[MAX_INPUT], strOutput[MAX_OUTPUT], *retStr = NULL;
	int c = 0, i = 0;
	memset(strInput, 0 , MAX_INPUT);
	
	// input data
	printf("Enter some text: \n");
	while ((c = getchar()) != EOF && i < MAX_INPUT){
		if (c == NEWLINE){
			c = SPACE;
		}

		*(strInput + i) = c;
		i++;
	}

	// put the data into type-justified format
	retStr = typeJustify(strOutput, strInput);

	// output the result
	printf("Type-justified text: \n");
	printf("%s\n", retStr);
	
	return EXIT_SUCCESS;
}

/* Logs:
	* works for multiple line programs with even number of spaces

	What breaks my program:
	* one really long line with no spaces that exceeds 65 chars 
		
	What doesnt work quite right:
	* one word seperated by a huge gap followed by another word -> I want the two words to be next to each other (needs new line manipulation)

*/

char *typeJustify(char *desBlock, char *srcBlock)
{
	char *retPtr = NULL, *allignedStr = NULL, margin[MARG_SIZE], line[MAX_CHARS + MARG_SIZE], buffer[BUFFER_SIZE];
	unsigned int bytesRead = 0, srcLength = 0, i = 0, seekPos = 0, charsToRead = 0;
	unsigned int totalBlanks = 0, checkPos = 0;
	unsigned int needToAllign = FALSE;
	int offset = 0, firstSeek = TRUE, blanksRemovedFront = 0, blanksRemovedBack = 0;

	// returns the offset from str where there are no blanks at the beginning
	int removeInitialBlanks(const char *str);
	int removeTrailingBlanks(char *str);

	// clean up function, returns > 0 if error and 0 if success
	void removeBlanksSrc(char *str);
	
	// find length of src
	memset(desBlock, 0, MAX_OUTPUT);
    removeBlanksSrc(srcBlock);
	srcLength = strlen(srcBlock);
		
	// construct the margin to be used later
	memset(margin, 0, MARG_SIZE);
	for (i = 0; i < MARG_SIZE; i++){
		strcat(margin, BLANK);
	}

	while (bytesRead < srcLength){
		needToAllign = FALSE;
		totalBlanks = 0;
		charsToRead = MAX_CHARS;
		memset(buffer, 0 , MAX_CHARS);
		memset(line, 0, MAX_CHARS + MARG_SIZE);
		
		// since arrays start at index 0, initially to read 65 chars we want seek up to the 64 index
		if (firstSeek){
			seekPos = bytesRead + (MAX_CHARS - 1);
		}
		
		else{
			seekPos = MAX_CHARS;
			firstSeek = FALSE;
		}

		// checks whether we have reached the last line
		if (seekPos < srcLength){
			checkPos = seekPos;
			// word is cut off
			if (srcBlock[seekPos] != SPACE && srcBlock[seekPos + 1] != SPACE){ 
				// calculate how many spaces we will need as well as 
				// how many characters we will be copying
				while (srcBlock[checkPos] != SPACE){
					checkPos--;
					charsToRead--;
					totalBlanks++;
				}

				// dont bother reading the space					
				charsToRead--; 
				totalBlanks++; // works but why?
				needToAllign = TRUE;
				printf("Path 1.\n");
			}

			// last char in the line is a space
			if (srcBlock[seekPos] == SPACE){
				// if the last part of the line contains spaces, we still need to allign it to the right margin
				while (srcBlock[checkPos] == SPACE){
					checkPos--;
					charsToRead--;
					totalBlanks++;
				}

				// charsToRead--;

				needToAllign = TRUE;
				printf("Path 2.\n");
			}

		}

		else{
			// we have reached the last line
			printf("Else part.\n");
			charsToRead = strchr(srcBlock, NULL_CHAR) - (srcBlock + bytesRead);
		}
	
		printf("needToAllign = %s\ncharsToRead = %d.\n", (needToAllign) ? "TRUE" : "FALSE", charsToRead);
		
		// copy the specified number of chars into buffer	
		copySections(buffer, srcBlock, bytesRead, charsToRead); 
		printf("[BEFORE ALLIGNING] Buffer: \n%sstrlen(buffer) = %d.\nNumber of blanks = %d.\n", buffer, (int) strlen(buffer), totalBlanks);
		 // length of each line should be 66 including newline chr
		
		// remove blanks at the start of the line
		blanksRemovedFront = removeInitialBlanks(buffer);
		offset = blanksRemovedFront;
		blanksRemovedBack = removeTrailingBlanks(buffer + offset);
		
		// if blanks or spaces were removed from the start then we need to allign
		if (offset || blanksRemovedBack){
			needToAllign = TRUE;
		}

		// add in the margin
		strcat(line, margin);

		// allign the text
		if (needToAllign){
			allignedStr = allignText(buffer + offset, totalBlanks, (offset + blanksRemovedBack));
			strcat(line, allignedStr);
			printf("[AFTER ALLIGNING]: allignedStr = \n%sstrlen(allignedStr) = %d.\nNumber of blanks = %d\n", allignedStr, (int) strlen(allignedStr), totalBlanks);
		}

		// no need to allign last line or short text
		else{
			strcat(line, buffer + offset);
			printf("[AFTER ALLIGNING]: buffer = \n%sstrlen(buffer) = %d.\nNumber of blanks = %d\n", buffer + offset, (int) strlen(buffer + offset), totalBlanks);
		}

		printf("line: \n%s\n", line);
		strcat(desBlock, line);

		bytesRead += charsToRead;
	}
	
	retPtr = desBlock;
	return retPtr;
}

// lots of processing
void removeBlanksSrc(char *text)
{
	char *ptrSpace = NULL, *firstSpacePtr = NULL;
	printf("Trying to remove blanks from src.\n");
	/* shift up or down */
	ptrSpace = strchr(text, SPACE);
    
	while (ptrSpace != NULL){
		// check if there are spaces trailing towards the right     
		firstSpacePtr = ptrSpace;
		*(firstSpacePtr + 1) = NULL_CHAR;
		// *(firstSpacePtr + 2) = NULL_CHAR;
		while (*ptrSpace == SPACE){
			ptrSpace++;
		}

		// squeeze the array together
		text = strcat(text, ptrSpace);
		ptrSpace = strchr(ptrSpace + 1, SPACE);
	}
}

int removeTrailingBlanks(char *str)
{
	char *spacePtr = NULL;
	int blanksRemoved = 0;

	// find the last space
	spacePtr = strrchr(str, SPACE);
	
	// check if a null char follows
	if (spacePtr != NULL){
		spacePtr += 1;
		if (*spacePtr == NULL_CHAR){
			spacePtr -= 1;
			while (*spacePtr == SPACE){
				blanksRemoved++;
				spacePtr--;
			}

			if (*spacePtr != SPACE){
				spacePtr += 1;
				if (*spacePtr == SPACE){
					*spacePtr = NULL_CHAR;
				}

			}
		}
	}
	

	return blanksRemoved;
}

int removeInitialBlanks(const char *str)
{
	int i = 0;
	for (i = 0; i < strlen(str); i++){
		if (str[i] != SPACE){
			break;
		}
	}

	return i;
}

char *allignText(char *line, const int blanksToAddFront, const int blanksToAddBack)
{
	char *retPtr = NULL;
	int allignSuccess = FALSE;

	int allignLeft(char *str, const int blanksToAdd);
	int allignRight(char *str, const int balanceBlanks);

	// do the alligning
	allignSuccess = allignLeft(line, blanksToAddFront);
	if (!allignSuccess){
		printf("Error alligning text to left margin.\n");
	}

	allignSuccess = allignRight(line, blanksToAddBack);
	if (!allignSuccess){
		printf("No need to allign to right margin\n");
	}

	retPtr = line;
	return retPtr;
}

int allignLeft(char *str, const int totalBlanks)
{
	char *startLinePtr = NULL, *blankPtr = NULL, *nullPtr = NULL, *newLinePtr = NULL;
	int blanksAdded = 0, returnValue = FALSE;
	
	// remember where the line starts
	startLinePtr = str;

	// search for a space in the line
	blankPtr = strchr(str, SPACE);
	// printf("seg fault here.\n");
	if (blankPtr == NULL){
		printf("No spaces found, not going to allign to left margin.\n");
	}

	else{
		printf("Alligning to the left.\n");
		// allign towards the left margin
		while (blanksAdded < totalBlanks){
			// shift the line array up to allow space for the extra space
			shiftArrayUp(blankPtr);
			nullPtr = strchr(blankPtr, NULL_CHAR);
			if (nullPtr == NULL){
				printf("Error adding the extra space after shifting.\n");
			}

			else{
				*nullPtr = SPACE;
			}

			// find the next space
			blankPtr = strchr(blankPtr + PATTERN_LEFT, SPACE);
			if (blankPtr == NULL){
				blankPtr = startLinePtr;
			}

			blanksAdded++;
		}
		
		// add the null char at the end of the str to properly terminate it
		newLinePtr = addNullAfterNl(str);
		if (newLinePtr == NULL){
			printf("Error unable to add null char after new line char.\n");
		}

		returnValue = TRUE;
	}

	return returnValue;
}


/* need to remove any trailing spaces before alligning */
int allignRight(char *str, const int balanceBlanks)
{
	char *nullPtr = NULL, *spacePtr = NULL, *startLinePtr = NULL, *newLinePtr = NULL;
	int fillToRight = 0, blanksAdded = 0, returnValue = 0;
	// int determineBlanksRight(const char *line);
	startLinePtr = str;

	// detect whether the line needs to be alligned to the right margin
	nullPtr = strchr(str, NULL_CHAR);
	fillToRight = MAX_CHARS - (nullPtr - str); // need a better method
	//fillToRight = determineBlanksRight(str);
	printf("fillToRight1 = %d.\n", fillToRight);
	
	fillToRight += balanceBlanks;
	if (fillToRight){
		printf("Alligning to the right.\n");
		blanksAdded = 0;
		printf("fillToRight2 = %d.\n", fillToRight);
		spacePtr = strrchr(str, SPACE);

		// printf("spacePtr - 1 = %c and *spacePtr = %c and spacePtr + 1 = %c\n", *(spacePtr - 1), *spacePtr, *(spacePtr + 1)); -> causes buffer overflow
		while (blanksAdded < fillToRight && spacePtr != NULL){
			shiftArrayUp(spacePtr);
			nullPtr = strchr(str, NULL_CHAR);
			if (nullPtr == NULL){
				printf("Error finding null char while shifting to the right.\n");
			}
	
			else{
				*nullPtr = SPACE;
			}

			spacePtr = strrchr(spacePtr - PATTERN_RIGHT, SPACE);
			if (spacePtr == NULL){
				spacePtr = startLinePtr;
			}

			blanksAdded++;
		}
		
		newLinePtr = addNullAfterNl(str);
		if (newLinePtr == NULL){
			printf("Error unable to add null char after new line char.\n");
		}

		returnValue = TRUE;
	}
	
	return returnValue;
}

char *addNullAfterNl(char *str)
{
	char *newLinePtr = NULL, *retPtr = NULL;
		
	newLinePtr = strchr(str, NEWLINE);
	if (newLinePtr != NULL){
		*(newLinePtr + 1) = NULL_CHAR;
		retPtr = str;
	}

	else{
		// if a new line char isnt found then one of the earlier functions isnt working correctly
		printf("Error: couldn't find a newline char.\n");
		exit(1);	
	}

	return retPtr;

}

// leaves the null character next to the space character
char *shiftArrayUp(char *array)
{
	char *retPtr = NULL;
	char *nullPtr = NULL;
	char temp;
	int i = 0;
		
	nullPtr = strchr(array, NULL_CHAR); 
	i = (nullPtr - array) - 1; // pointer arithmetic
	
	while (i >= 0){
		temp = array[i];
		array[i] = array[i + 1];
		array[i + 1] = temp;
		i--;
	}

	retPtr = array;
	return retPtr;
}

char *copySections(char *des, const char *src, const unsigned int startPos, const int numberOfChars)
{
	int i = 0, j = 0;
	char *retPtr = NULL;

	for (i = 0; i < numberOfChars; i++, j++){
		des[i] = src[startPos + j];
	}

	des[i] = NEWLINE;
	des[i + 1] = NULL_CHAR;
 
	retPtr = des;
	return retPtr;
}

