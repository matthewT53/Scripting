#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef char * string;
typedef int * intPtr;

void f1(const char *s1, char **strPtr);
void test1(void);

int main(void)
{
	int a = 15;
	int *b;
	int **c;
	// pointer to a pointer to a pointer
	int ***d;
	char *str = "hello world", *ptr2 = NULL;
	intPtr ptr = NULL;
	string mystring = "hello world"; 
	
	b = &a;
	c = &b;
	d = &c;
	ptr = &a;
	printf("Value of *ptr = %d.\n", *ptr);
	printf("mystring = %s\n", mystring);
	printf("Value of a = %d and address of a: %p.\n", a, &a);
	printf("B points to %p and address of B: %p.\n", b, &b);
	printf("c points to: %p. and address of c is: %p\n", c, &c);
	printf("d points to: %p and address of d is: %p.\n", d, &d);

	// printf("57 a digit? %d.\n", isdigit('57'));

	printf("Newline is %d.\n", ispunct('\n'));

	// testing const qualifier
	f1(str, &ptr2);
	printf("ptr2 = %s.\n", ptr2);
	printf("Address of ptr2: %p and address that ptr2 points to: %p\n", &ptr2, ptr2);
	test1();

	return EXIT_SUCCESS;
}

void test1(void)
{
	char buffer[250];
	memset(buffer, 0, 250);
	printf("sizeof(buffer) = %ld.\n", sizeof(buffer));

	char *bufPtr = NULL;
	bufPtr = buffer;
	printf("sizeof(bufPtr) = %ld.\n", sizeof(*bufPtr));


}

void f1(const char *s1, char **strPtr)
{
	char temp[56];
	temp[0] = s1[0];
	temp[1] = s1[1];
	temp[2] = s1[2];
	temp[3] = '\0';
	printf("Address of temp: %p.\n", temp);
	*strPtr = (char *) (s1 + 3);
	long int distance = 0;
	// this produces an error
	distance = (s1 + 5) - (s1);	
	printf("%ld\n", distance);
	char *string = "484960458.6456456456645";
	assert(atof(string) == 484960458.6456456456645);

}
