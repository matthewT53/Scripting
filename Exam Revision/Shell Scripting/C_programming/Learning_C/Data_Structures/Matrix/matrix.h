/*
	Name: Matthew Ta
	Date: 13/11/2015
	Description: Matrix ADT interface
*/

typedef struct _matrixRep *Matrix;

Matrix newMatrix(const int n, const int m); // creates a new matrix with n rows and m columns
void disposeMatrix(Matrix mt);

void fillMatrix(Matrix mt, const int max); // fill a matrix m with random values from 0 -> max - 1
Matrix add(Matrix m1, Matrix m2); // adds two matrices
Matrix multiply(Matrix m1, Matrix m2); // multiplies two matrices

// getter functions
int getNumCols(Matrix mt); // returns # cols of a matrix
int getNumRows(Matrix mt); // returns # rows of a matrix 
int isSquare(Matrix mt);  // returns true if # cols == # rows
int getElement(Matrix mt, const int i, const int j); // returns num at m[i][j]

void insertValues(Matrix mt, const int values[], const int size); // insert values into the matrix

void showMatrix(Matrix mt); // prints a matrix 
