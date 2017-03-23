#include "serialMatrixMultiplication.h"
#include "matrixMultiplication.h"

int **serialMatrixMultiplication(int **m1, int **m2, int dim){
	return matrixMultiplication(m1, m2, 0, dim, dim);
}