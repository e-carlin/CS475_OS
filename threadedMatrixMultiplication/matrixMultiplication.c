#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrixMultiplication.h"

/*
* @param m1 one of the matrices to be mutiplied
* @param m2 the other matrix to be multiplied
* @param startResultRow the starting row we wish to calculate the result for (0 indexed, inclusive)
* @param endResultRow the ending row we wish to calculate the resutl for (0 indexed, exclusive)
* @param dim the dimensions of the input arrays (assumed to be the same dimensions and squar)
* @return the resulting rows we wanted to calculate 
*/
int **matrixMultiplication(int **m1, int **m2, int startResultRow, int endResultRow, int dim){
	int **output = mallocMatrix(endResultRow - startResultRow, dim);

	int i,j,k;
	for(i = startResultRow; i < endResultRow; i++) {         // rows from m1
	    for(j = 0; j < dim; j++) {     // columns from m2
	        for(k = 0; k < dim; k++) { // columns from m1
	            output[i-startResultRow][j] += m1[i][k] * m2[k][j];
	        }
	    }
	}
	return output;
}

/*
* Creates a matrix filled with random values
* @param dim the dimensions of the matrix
* @return the matrix
*/
int **generateRandomMatrix(int dim){
	//Allocate space for new array
	int **matrix = mallocMatrix(dim, dim);

	//Seed random integer maker with current time so we get different random ints every time
	srand(time(NULL));

	int i,j,r;
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			//Generate a random int in between 0 and 99
			r = rand() % 100;
			matrix[i][j] = r;
		}
	}
	return matrix;
}

/*
* Prints a matrix
* @param matrix the matrix to print
* @param rows the number of rows to print
* @param cols the number of cols to print
*/
void printMatrix(int **matrix, int rows, int cols){
	int i,j;
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/*
* Allocates space for a new matrix with row*col dimensions
* @param row the number of rows in the matrix
* @param col the number of columns in the matrix
* @return the matrix on the heap
*/
int **mallocMatrix(int row, int col){
	int **matrix = (int **)malloc(row * sizeof(int *));
	int i,j;

	//Allocate space
    for (i=0; i<row; i++){
         matrix[i] = (int *)malloc(col * sizeof(int));
     }

     //Set all values to 0
     for(i=0; i<row; i++){
     	for(j=0; j<col; j++){
     		matrix[i][j] = 0;
     	}
     }

     return matrix;
}

