#include <stdlib.h>
#include "matrixMultiplication.h"
/*
* @param m1 one of the matrices to be mutiplied
* @param m2 the other matrix to be multiplied
* @param dim the dimension of the matrix (all matrices are assumed to be square)
* @param numResultRows the number of rows of the putput matrix to be calculated 
*/
int **matrixMultiplication(int **m1, int **m2, int dim, int numResultRows){
	int **output = (int **) malloc(sizeof(int)*dim*numResultRows);

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

int **generateRandomMatrix(int dim){
	return 0;
}