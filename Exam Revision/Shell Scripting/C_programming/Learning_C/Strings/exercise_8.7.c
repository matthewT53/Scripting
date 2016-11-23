#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define SIZE 100
#define NUM_INTS 4

int main(void)
{
	int sum = 0;
	char s1[SIZE], s2[SIZE], s3[SIZE], s4[SIZE];
	int objectsRead = 0;
	printf("Enter four strings: \n");
	objectsRead = scanf("%s%s%s%s", s1, s2, s3, s4);
	printf("(DEBUG) Total objects read: %d.\n", objectsRead);
	// printf("%s %s %s %s\n", s1, s2, s3, s4);
	sum = atoi(s1) + atoi(s2) + atoi(s3) + atoi(s4);
	printf("Sum is: %d.\n", sum);

	return 0;
}
