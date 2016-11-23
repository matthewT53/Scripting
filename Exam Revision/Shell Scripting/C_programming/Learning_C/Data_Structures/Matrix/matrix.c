/*
	Name: Matthew Ta
	Date: 13/11/2015
	Description: Matrix ADT implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "matrix.h"

#define TRUE 1
#define FALSE 0

typedef struct _matrixRep{
	int **m; // the actual matrix
	int nRows; // # rows
	int nCols; // # cols
} matrixRep;

// creates a new matrix
Matrix newMatrix(const int n, const int m)
{
	int i = 0;
	Matrix mt = malloc(sizeof(matrixRep));
	assert(mt != NULL); 

	mt->m = malloc(sizeof(int *) * n); // create n rows
	for (i = 0; i < n; i++){
		mt->m[i] = calloc(m, sizeof(int)); // create m columns
	} 
	
	mt->nRows = n;
	mt->nCols = m;
	return mt;
}

// fills a matrix with random values
void fillMatrix(Matrix mt, const int max)
{
	int i = 0, j = 0;
	srand(time(NULL) + (1 + rand() % max)); // randomize the values
	if (mt != NULL && mt->m != NULL){
		for (i = 0; i < mt->nRows; i++){
			for (j = 0; j < mt->nCols; j++){
				mt->m[i][j] = rand() % max;
			}
		}	
	}
}

// frees a matrix
void disposeMatrix(Matrix mt)
{
	if (mt != NULL && mt->m != NULL){
		int i = 0;
		for (i = 0; i < mt->nRows; i++){
			free(mt->m[i]); // free each row
		}
		free(mt->m); // free the 2d array
		free(mt); // free the matrix
	}
}

// adds two matrices together
Matrix add(Matrix m1, Matrix m2) // O(RC) complexity
{
	int i = 0, j = 0;
	Matrix result = NULL;
	if (m1 != NULL && m2 != NULL){
		if (m1->m != NULL && m2->m != NULL){
			if (m1->nRows == m2->nRows && m1->nCols == m2->nCols){ // ensure the matrices are of the same size
				result = newMatrix(m1->nRows, m1->nCols);
				for (i = 0; i < m1->nRows; i++){
					for (j = 0; j < m1->nCols; j++){ // pick something that is not in common
						result->m[i][j] = m1->m[i][j] + m2->m[i][j];
					}
				}
			}
		}
	}
	return result;
}

// multiplies two matrices together
Matrix multiply(Matrix m1, Matrix m2)
{
	int i = 0, j = 0, k = 0;
	Matrix result = NULL;
	if (m1 != NULL && m2 != NULL){
		if (m1->nCols == m2->nRows){ // compatibility test
			result = newMatrix(m1->nRows, m2->nCols); // create the new matrix to store the result
			for (i = 0; i < m1->nRows; i++){
				for (j = 0; j < m2->nCols; j++){
					for (k = 0; k < m1->nCols; k++){ // doesn't matter which one we use rows or cols
						result->m[i][j] += (m1->m[i][k] * m2->m[k][j]);
					}
				}	
			}
		}
	}
	return result;
}

// returns # columns
int getNumCols(Matrix mt)
{
	int n = 0;
	if (mt != NULL){
		n = mt->nCols;
	}
	return n;
}

// returns # rows
int getNumRows(Matrix mt)
{
	int n = 0;
	if (mt != NULL){
		n = mt->nRows;
	}
	return n;
}

// determines if a matrix is a square matrix
int isSquare(Matrix mt)
{
	int ret = FALSE;
	if (mt != NULL){
		if (mt->nCols == mt->nRows){
			ret = TRUE;
		}
	}
	return ret;
}

// gets the num at m[i][j]
int getElement(Matrix mt, const int i, const int j)
{	
	int n = 0;
	if (i < mt->nRows && j < mt->nCols){
		n = mt->m[i][j];
	}
	return n;
}

// insert values into the matrix
void insertValues(Matrix mt, const int values[], const int size)
{
	int i, j, k;
	assert(size == (mt->nCols * mt->nRows));
	assert(mt != NULL && mt->m != NULL);
	for (i = 0, k = 0; i < mt->nRows; i++){
		for (j = 0; j < mt->nCols; j++){
			mt->m[i][j] = values[k++];
		}
	}
}

// print the matrix
void showMatrix(Matrix mt)
{
	assert(mt != NULL && mt->m != NULL);
	int i = 0, j = 0;

	for (i = 0; i < mt->nRows; i++){
		printf("[");
		for (j = 0; j < mt->nCols; j++){
			printf("%3d%c", mt->m[i][j], (j != mt->nCols - 1) ? ',' : ' ');	
		}
		printf("]\n");
	}
}




