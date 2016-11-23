#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define SIZE 100

void printUpperCase(const char *);
void printLowerCase(const char *);
void test(void);

int main(void)
{
	test();
	return EXIT_SUCCESS;
}

void test(void){
	// test an empy string
	char *s0 = "";
	printf("Test 1: %s\n", s0);
	printUpperCase(s0);
	printLowerCase(s0);
	printf("\n");

	// test a string already in lower case
	char *s1 = "hello world";
	printf("Test 2: %s\n", s1);
	printUpperCase(s1);
	printLowerCase(s1);
	printf("\n");

	// test a string in upper case
	char *s2 = "HELLO WORLD";
	printf("Test 3: %s\n", s2);
	printUpperCase(s2);
	printLowerCase(s2);
	printf("\n");

	// test a string with a mixture of both
	char *s3 = "heLLo WOrLD";
	printf("Test 4: %s\n", s3);
	printUpperCase(s3);
	printLowerCase(s3);
	printf("\n");

}

void printUpperCase(const char *string)
{
	int i = 0;

	for (i = 0; *(string + i) != '\0'; i++){
		printf("%c", toupper(*(string + i)));
	}

	printf("\n");
}
	
void printLowerCase(const char *string){
	int i = 0;

	for (i = 0; string[i] != '\0'; i++){
		printf("%c", tolower(string[i]));
	}

	printf("\n");
}
