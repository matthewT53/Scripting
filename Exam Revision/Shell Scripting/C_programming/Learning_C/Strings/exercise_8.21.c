/* 
	Name: Matthew Ta
	Date: 3/7/2015
	Description: This program sorts a list of strins in alphabetical order
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 15

#define NEWLINE '\n'
#define NULL_CHAR '\0'

int main(void)
{
	char *listStrings[MAX_LENGTH] = {"Moorebank", "Wattle groove", "Georges fair", "Bankstown", "Merrylands", "Central", "Redfern", "Auburn", "Chipping Norton", "Greenacre",
					"Hammondville", "Condell park", "Newbridge", "Liverpool", "Hoxton park"};
	char *temp = NULL;
	// now sort the strings in alphabetical order
	int i = 0, j = 0;
	
	// output the list before sorting
	printf("[BEFORE SORT]:\n");
	for (i = 0; i < MAX_LENGTH; i++){
		printf("%s\n", listStrings[i]);
	}

	printf("\n");

	// now sort the list in alphabetical order
	for (i = 0; i < MAX_LENGTH; i++){
		for (j = 0; j < MAX_LENGTH - 1; j++){
			if (strcmp(listStrings[j], listStrings[j + 1]) > 0){
				temp = listStrings[j];
				listStrings[j] = listStrings[j + 1];
				listStrings[j + 1] = temp;
			}
		}
	}

	// now output the sorted list
	printf("[AFTER SORT]: \n");
	for (i = 0; i < MAX_LENGTH; i++){
		printf("%s\n", listStrings[i]);
	}
	
	return 0;
}
