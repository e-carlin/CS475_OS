#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "matrixMultiplication.h"
#include "sequentialMatrixMultiplication.h"
#define usage "Usage: ./mmm <mode> [num threads] <size>"

int main(int argc, char *argv[]){
	struct timezone Tzp;
	struct timeval Tp;

    gettimeofday (&Tp, &Tzp);
    printf("start %f\n", Tp.tv_sec + Tp.tv_usec*1.0e-6);



	//Want to do sequential multiplication
	if(argc == 3 && strcmp(argv[1], "S") == 0){
		printf("*****sequential****\n");
		printf("%s\n", argv[2]);
		int dim = atoi(argv[2]);
		printf("%d\n", dim);

		//Creates the matrices to multiply together
		int **m1 = generateRandomMatrix(dim);
		int **m2 = generateRandomMatrix(dim);

		int **sequentialMultiplication = sequentialMatrixMultiplication(m1, m2, dim);
		printf("\nSequential Result\n");
		printMatrix(sequentialMultiplication, dim, dim);

		gettimeofday (&Tp, &Tzp);
		printf("end %f\n", Tp.tv_sec + Tp.tv_usec*1.0e-6);

		return 0;
	}

	//Want to do parallel computations
	else if(argc == 4 && strcmp(argv[1], "P") == 0){
		printf("**** Parallel *****\n");
		
		return 0;
	}

	else{
		printf("%s\n", usage);
		exit(1);
	}

	return 1;
}