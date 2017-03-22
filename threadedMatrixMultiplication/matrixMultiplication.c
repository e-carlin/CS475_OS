#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrixMultiplication.h"
/*
* @param m1 one of the matrices to be mutiplied
* @param m2 the other matrix to be multiplied
* @param dim the dimension of the matrix (all matrices are assumed to be square)
* @param numResultRows the number of rows of the putput matrix to be calculated 
*/
int **matrixMultiplication(int **m1, int **m2, int dim, int numResultRows){
	int **output = mallocMatrix(numResultRows, dim);

	int i,j,k;
	for(i = 0; i < numResultRows; i++) {         // rows from m1
	    for(j = 0; j < dim; j++) {     // columns from m2
	        for(k = 0; k < dim; k++) { // columns from m1
	            output[i][j] += m1[i][k] * m2[k][j];
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
* @param dim the dimensions of the matrix (all matrices are assumed to be square)
*/
void printMatrix(int **matrix, int dim){
	int i,j;
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
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

