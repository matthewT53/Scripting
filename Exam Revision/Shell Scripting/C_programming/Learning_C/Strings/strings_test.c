#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void){
	int a = 10;
	int *b, *c;
	char *string = "This is a string";
	void *v;

	b = &a;
	
	printf("Address B points to: %p\n", b);
	// printf("Address c points to: %p\n", c);
	c = b;
	v = c;
	printf("Value of v = %p.\n", v);
	printf("Address c points to: %p\n", c);
	printf("Size of int pointer = %d.\nSize of char pointer = %d.\n", (int) sizeof(b), (int) sizeof(string));
	printf("Address that the string is stored in: %p.\n", &string);
	
	printf("Number is %s.\n", (*b == 16) ? "true" : "false");

	// loop through string using pointer arithmetic
	while (*string != '\0'){
		printf("%c", *string);
		string++;
	}
	printf("\n");
	return EXIT_SUCCESS;
}
