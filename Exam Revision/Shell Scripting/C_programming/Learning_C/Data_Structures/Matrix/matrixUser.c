/*
	Name: Matthew Ta
	Date: 13/11/2015
	Description: User of the matrix ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

void test(void);
void test1(void); // tests the multiplication function

int main(void)
{
	test1();
	return EXIT_SUCCESS;
}

void test(void)
{
	Matrix m = newMatrix(4,4);
	fillMatrix(m, 100);
	printf("Matrix 1:\n");
	showMatrix(m);

	Matrix n = newMatrix(4,4);
	fillMatrix(n, 100);
	printf("Matrix 2:\n");
	showMatrix(n);
	
	printf("Adding the two matrices:\n");
	Matrix r = add(m,n);
	showMatrix(r);
	
	printf("Testing the insertion function.\n");
	int a[4] = {1,2,3,4};
	Matrix s = newMatrix(2,2);
	insertValues(s, a, 4);
	showMatrix(s);	
	
	disposeMatrix(s);
	disposeMatrix(n);
	disposeMatrix(m);
	disposeMatrix(r);
}

void test1(void)
{
	//int i = 0, j = 0;
	printf("Testing the multiply() function.\n");
	
	printf("Testing empty matrix.\n");
	Matrix m = newMatrix(0, 0);
	Matrix n = newMatrix(4,5);
	fillMatrix(m, 100);
	fillMatrix(n, 100);
	Matrix r = multiply(m,n);
	assert(r == NULL);
	disposeMatrix(m);
	disposeMatrix(n);
	disposeMatrix(r);
	printf("Passsed first test.\n");
	
	m = newMatrix(0, 0);
	n = newMatrix(0, 0);
	fillMatrix(m, 100);
	fillMatrix(n, 100);
	r = multiply(m,n);
	assert(r != NULL);
	assert(getNumRows(r) == 0 && getNumCols(r) == 0);
	disposeMatrix(m);
	disposeMatrix(n);
	disposeMatrix(r);
	printf("Passed.\n");

	printf("Testing multiplying two square matrices.\n");
	int a[4] = {1,2,3,4};
	int a1[4] = {4,3,2,5};
	m = newMatrix(2,2);
	n = newMatrix(2,2);
	insertValues(m, a, 4);	
	insertValues(n, a1, 4);
	
	showMatrix(m);
	showMatrix(n);

	r = multiply(m, n);
	showMatrix(r);
	assert(getElement(r, 0, 0) == 8);
	assert(getElement(r, 0, 1) == 13);
	assert(getElement(r, 1, 0) == 20);
	assert(getElement(r, 1, 1) == 29);
	disposeMatrix(m);
	disposeMatrix(n);
	disposeMatrix(r);
	printf("Passed.\n");

	printf("Testing with two comptible matrices with different sizes.\n");
	m = newMatrix(2,3);
	n = newMatrix(3,4);
	int a2[6] = {1,2,3,4,5,6};
	int a3[12] = {7,8,9,10,11,12,13,14,15,16,17,18};
	printf("Matrix 1:\n");
	insertValues(m, a2, 6);
	showMatrix(m);	
	printf("Matrix 2:\n");
	insertValues(n, a3, 12);
	showMatrix(n);
	r = multiply(m, n);
	printf("Result:\n");
	showMatrix(r);
	
	assert(getNumRows(r) == 2);
	assert(getNumCols(r) == 4);
	assert(getElement(r, 0, 0) == 74);
	assert(getElement(r, 0, 1) == 80);
	assert(getElement(r, 0, 2) == 86);	
	assert(getElement(r, 0, 3) == 92);
	assert(getElement(r, 1, 0) == 173);
	assert(getElement(r, 1, 1) == 188);
	assert(getElement(r, 1, 2) == 203);
	assert(getElement(r, 1, 3) == 218);	
	disposeMatrix(m);
	disposeMatrix(n);
	disposeMatrix(r);
	printf("Passed.\n");

	printf("Testing with two imcompatible matrices.\n");
	m = newMatrix(2,2);
	n = newMatrix(3,3);
	int a4[4] = {1,2,3,4};
	int a5[9] = {5,6,7,8,9,10,11,12,13};
	insertValues(m, a4, 4);
	insertValues(n, a5, 9);
	r = multiply(m, n);
	assert(r == NULL);
	disposeMatrix(r);
	disposeMatrix(m);
	disposeMatrix(n);
	printf("Passed.\n");

	printf("Passed all tests, you are awesome!\n");
}
