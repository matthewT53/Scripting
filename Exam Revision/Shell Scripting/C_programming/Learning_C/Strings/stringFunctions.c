#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void test(char *str);
void *test1(void *str, void *str1, int n);

int main(void)
{
	double d;
	unsigned long int x = 0;
	char *string = "56.8790 huele", string2[35] = "12312423423423 dasdas";
	char *remainderPtr, *remainderPtr2;
	char c = EOF;
	printf("%s", &string2[1]);
	// testing strtod
	d = strtod(string, &remainderPtr);
	printf("Converted string looks like: %.4f and %s\n", d, remainderPtr);
	x = strtoul(string2, &remainderPtr2, 0);
	printf("Converted string looks like: %lu and %s\n", x, remainderPtr2);
	printf("EOF: %d.\n", c);

	// testing strcpy and strcat
	char string1[25];
	char *newstring = strcpy(string1, string2);
	printf("New string is %s.\n", newstring);
	char string3[40] = "hello friends";
	newstring = strcat(string3, string2);
	printf("Concat string is %s.\n", newstring);
	
	char *s2 = "Hello friend";
	char s1[40] = "hello yolo";
	size_t strLength = 6;
	char *newstring2 = strncat(s1, s2, strLength);
	// need to copy the null terminating char
	printf("newString2: %s.\n", newstring2); 

	char c2 = 'a';
	char *convolutedString = "drsfsdfAasfbsdsjkdklsfklsdLFKSDLFSDLKFnKLFnksdlfnlsdFNDSLFK";
	printf("Result: %c.\n", *strchr(convolutedString, c2));


	char a[50] = "Jack", b[50];
	printf("%s\n", b);
	printf("%s\n", strcpy(b, a));

	char *str1 = "adt";
	char *str2 = "asdsadasas";
	unsigned int value = strspn(str1, str2);
	printf("value = %d.\n", value);

	char strs[100] = "friend asd";
	char *retPtr = strtok(strs, " ");
	printf("%s.\n", retPtr);	
	retPtr = strtok(NULL, " ");
	printf("%s.\n", retPtr);
	retPtr = strtok(NULL, " ");
	printf("%s.\n", retPtr);

	printf("strlen(strs) = %d.\n", (int) strlen(strs));
	str1 = "";
	str2 = NULL;
	printf("Length of str1 = %d.\n", (int) strlen(str1));

	char *str3 = "hello world";
	char *nullPtr = strchr(str3, '\0');
	assert(nullPtr != NULL && *nullPtr == '\0');
	test(str3);
	test(NULL);

	char *str4 = " ";
	printf("*str4 = %d.\n", *str4);

	char *str5 = "dasfsafsdgsd";
	char *str6 = "";
	retPtr = strstr(str5, str6);
	printf("retPtr = %p and *retPtr = %c.\n", retPtr, *retPtr);
	assert(retPtr != NULL && *retPtr == 'd');

	int array1[5] = {0};
	int array2[5] = {1,2,3,4,5};
	test1(array1, array2, 20);
	for (int i = 0; i < 5; i++){
		printf("array1[%d] = %d.\n", i, array1[i]);
	}

	char str8[] = "hello world";
	char str9[] = "sdkjnsdkjs";
	retPtr = test1(str8, str9, 5);
	printf("retPtr = %s.\n", retPtr);
	
	char str10[] = "Home Sweet Home";
	char str11[] = "Home Sweet";
	retPtr = memmove(&str10[5], str10, 10);
	printf("Address of str10: %p and &str10[5]: %p and str11: %p.\n", str10, &str10[5], str11);
	printf("retPtr = %s.\n", retPtr);

	return EXIT_SUCCESS;
}

void test(char *str)
{
	static char *strPtr = NULL;
	if (str != NULL){
		strPtr = str;
	}

	printf("Value = %c.\n", *strPtr);
	strPtr++;
	
}

void *test1(void *str, void *str1, int n)
{
	void *returnPtr = str;
	printf("Address pointed to by str: %p and str1: %p.\n", str, str1);
	char temp[n];
	for (int i = 0; i < n; i++, str++, str1++){
		*((char *) str) = *((char *) str1);
		temp[i] = *((char *) str);
		printf("temp[%d] = %c.\n", i, temp[i]);
	}

	return returnPtr;
}

	

