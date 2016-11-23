/*
	Matthew Ta
	How to create an array of 2-d arrays
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int a[5][5], b[5][5]; // testing array of 2-d arrays
	int (*c[])[5] = {a, b};
	int i =0, j = 0;

	int d[5] = {0}; // testing array of arrays
	int *e[1] = {d};

	printf("Testing array of 2-d arrays: \n");
	printf("a = %p and b = %p\n", a, b);
	printf("c[0] = %p and c[1] = %p\n", c[0], c[1]);

	printf("Showing a: \n");
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			a[i][j] = rand() % 100;
			printf("a[%d][%d] = %d\n", i, j, a[i][j]);
		}
	}

	printf("asd: %p\n", (c[0]));

	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			printf("c[0][%d][%d] = %d\n", i, j, (c[0])[i][j]);
		}
	}

	printf("Testing array of arrays: \n");
	for (i = 0; i < 5; i++){
		d[i] = rand() % 100;
		printf("d[%d] = %d\n", i, d[i]);
	}	

	for (i = 0; i < 5; i++){
		printf("e[0][%d] = %d\n", i, e[0][i]);
	}

	return EXIT_SUCCESS;
}
