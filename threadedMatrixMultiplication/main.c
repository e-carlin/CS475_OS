#include <stdio.h>
#include "matrixMultiplication.h"

int main(){
	int **m1 = generateRandomMatrix(3);
	int **m2 = generateRandomMatrix(3);

	printf("M1\n");
	printMatrix(m1, 3);

	printf("\nM2\n");
	printMatrix(m2, 3);


	int **result = matrixMultiplication(m1, m2, 3, 3);
	printf("\nResult\n");
	printMatrix(result, 3);

	return 1;
}