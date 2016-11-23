#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

int main(void)
{
	int cmpValue = 0, objectsRead = 0;
	char s1[SIZE], s2[SIZE];
	
	printf("Enter two strings: \n");
	objectsRead = scanf("%s%s", s1, s2);
	printf("(debug) Objects read = %d.\n", objectsRead);
	cmpValue = strcmp(s1, s2);

	if (cmpValue < 0){
		printf("First string is less than the second.\n");
	}

	else if (cmpValue > 0){
		printf("First string is greater than the second.\n");
	}

	else{
		printf("Both strings are equal.\n");
	}

	return 0;
}
