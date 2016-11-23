/*
	Author: Matthew Ta
	Date: 3/7/2015
	Description: Print characters of the ASCII chart

	After ASCII code 127, the program tries to print the characters of the extended ASCII set if it recognises them, this program run on ubuntu prints garbage characters after ASCII code 127.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX 255

void printAscii(void);

int main(void)
{
	int x = 0, objectsRead = 0;
	while (objectsRead != EOF){
		printf("Enter an ASCII code: \n");
		objectsRead = scanf("%d", &x);
		printf("Corresponding ASCII char is %c\n", x);
		printf("\n");
	}
	
	printAscii();

	return 0;
}

void printAscii(void)
{
	int i = 0;
	printf("Printing ASCII characters from 000 -> 255.\n");
	
	for (i = 0; i < MAX; i++){
		printf("%c\n", i);
	}
}
