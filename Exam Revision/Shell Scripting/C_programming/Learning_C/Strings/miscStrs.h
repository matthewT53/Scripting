/*
	Name: Matthew Ta
	Date: 1/8/2015
	Description: This header file contains function prototypes for helper string functions
*/

// fgets always adds a newline char, this function removes it
char *removeNewLine(char *str);

// remove duplicates of strings
char *removeDuplicates(char *str, const char *strToRemove);
