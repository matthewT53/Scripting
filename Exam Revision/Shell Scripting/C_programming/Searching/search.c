/*
	Name: Matthew Ta
	Date: 14/11/2015
	Description: Binary search
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100
#define NOT_FOUND -1 

int ncomps = 0; // global var to count comparisons

// tries to find x in the array, returns index if found and -1 otherwise
int binarySearch(int *a, int lo, int hi, int x);
int linearSearch(int *a, int lo, int hi, int x); 

int main(void)
{
	FILE *fp = NULL;
	int numRead = 0, i = 0, index = NOT_FOUND;
	int a[SIZE] = {0};
	
	// open file for reading
	fp = fopen("output.txt", "r");	
	assert(fp != NULL);
	
	// read all values into array
	while ( !EOF ){ // read while not EOF
		fscanf(fp, "%d", &numRead);
		a[i++] = numRead;		
	}

	// do the binary search
	index = linearSearch(a, 0, SIZE, 675);
	printf("(Linear search): \nFound = %s at Index = %d and ncomps = %d\n", (index >= 0) ? "TRUE" : "FALSE", index, ncomps);
	ncomps = 0; 
	index = binarySearch(a, 0, SIZE, 675);
	printf("(Binary search): \nFound = %s at Index = %d and ncomps = %d\n", (index >= 0 && index < SIZE) ? "TRUE" : "FALSE", index, ncomps); 

	fclose(fp);
	return EXIT_SUCCESS;
}

int binarySearch(int *a, int lo, int hi, int x)
{
	int mid = 0, index = NOT_FOUND;
	ncomps++;
	if (lo == hi){
		return lo;
	}	

	mid = (lo + hi) / 2;
	if (x < a[mid]){
		index = binarySearch(a, lo, mid, x);
	}

	else if (x > a[mid]){
		index = binarySearch(a, mid + 1, hi, x);
	}

	else{ // x == a[mid]
		return mid;
	}
	return index;
}

int linearSearch(int *a, int lo, int hi, int x)
{
	int i = 0;
	for (i = lo; i < hi; i++){
		if (a[i] == x){
			break;
		}
		ncomps++;
	}

	if (i == hi) { i = NOT_FOUND; }
	return i;
}


