#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "matrixMultiplication.h"
#include "sequentialMatrixMultiplication.h"
#include "parallelMatrixMultiplication.h"
#include "main.h"

#define usage "Usage: ./mmm <mode> [num threads] <size>"

int main(int argc, char *argv[]){
	struct timezone Tzp;
	struct timeval Tp;




	//Want to do sequential multiplication
	if(argc == 3 && strcmp(argv[1], "S") == 0){
		int dim = atoi(argv[2]);

		printf("==========\n");
		printf("mode: sequential\n");
		printf("thread count: 1\n");
		printf("size: %d\n", dim);
		printf("=========\n");

		//Creates the matrices to multiply together
		int **m1 = generateRandomMatrix(dim);
		int **m2 = generateRandomMatrix(dim);

		//Calcualte product and time result
		double startTime = getTime(Tzp, Tp);
		sequentialMatrixMultiplication(m1, m2, dim);
		double endTime = getTime(Tzp,Tp);

		printf("Sequential time: %f\n", endTime - startTime);

		// printf("\nSequential Result\n");
		// printMatrix(sequentialMultiplication, dim, dim);
		return 0;
	}

	//Want to do parallel computations
	else if(argc == 4 && strcmp(argv[1], "P") == 0){
		int dim = atoi(argv[3]);
		int threadCount = atoi(argv[2]);

		printf("==========\n");
		printf("mode: parallel\n");
		printf("thread count: %d\n", threadCount);
		printf("size: %d\n", dim);
		printf("=========\n");

		//Creates the matrices to multiply together
		int **m1 = generateRandomMatrix(dim);
		int **m2 = generateRandomMatrix(dim);

		//Do sequential multiplication
		double sequentialStartTime = getTime(Tzp, Tp);
		int **sequentialMultiplicationResult = sequentialMatrixMultiplication(m1, m2, dim);
		double sequentialEndTime = getTime(Tzp,Tp);
		printf("Sequential time: %f\n", sequentialEndTime - sequentialStartTime);

		//Do parallel multiplication
		double parallelStartTime = getTime(Tzp, Tp);
		int **parallelMultiplicationResult = parallelMatrixMultiplication(m1, m2, dim, threadCount);
		double parallelEndTime = getTime(Tzp,Tp);
		printf("parallel time: %f\n", parallelEndTime - parallelStartTime);
		

		printf("***** SEQUENTIAL *******\n");
		printMatrix(sequentialMultiplicationResult, dim, dim);
		printf("************************\n\n");

		printf("****** PARALLEL **********\n");
		printMatrix(parallelMultiplicationResult, dim, dim);
		printf("**************************\n\n");


		//TODO: change this to actually evaluate the parallel vs sequential matrices
		double maxDifference = maxMatrixDifference(sequentialMultiplicationResult, parallelMultiplicationResult, dim);
		printf("Verifying... largest error between parallel and sequential multiplication %f\n", maxDifference);
		return 0;
	}

	else{
		printf("%s\n", usage);
		exit(1);
	}

	return 1;
}

double getTime(	struct timezone Tzp, struct timeval Tp){
	int stat;

	stat = gettimeofday (&Tp, &Tzp);
	if (stat != 0){
	    printf("Error return from gettimeofday: %d",stat);
	    return -1;
	}
	return Tp.tv_sec + Tp.tv_usec*1.0e-6;
}