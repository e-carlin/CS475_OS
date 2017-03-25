#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "matrixMultiplication.h"
#include "sequentialMatrixMultiplication.h"
#include "parallelMatrixMultiplication.h"
#include "main.h"

#define usage "Usage: ./mmm <mode> [num threads] <size>"
#define numTimesToRun 3

/*
* Prompts the user to run sequential vs parallel matrix multiplication
* and displays execution time differences.
*/
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
		return 0;
	}

	//Want to do parallel computations
	else if(argc == 4 && strcmp(argv[1], "P") == 0){
		int i;
		double startTime, endTime;
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
		double totalSequentialRunTime;
		int **sequentialMultiplicationResult;

		for(i=0; i<numTimesToRun+1; i++){
			startTime = getTime(Tzp, Tp);
			sequentialMultiplicationResult = sequentialMatrixMultiplication(m1, m2, dim);
			endTime = getTime(Tzp,Tp);

			//Only keep results after the first run to allow the cache to warm up
			if(i != 0){
				totalSequentialRunTime += endTime - startTime;
			}
		}
		
		//Do parallel multiplication
		double totalParallelRunTime;
		int **parallelMultiplicationResult;

		for(i=0; i<numTimesToRun+1; i++){
			startTime = getTime(Tzp, Tp);
			parallelMultiplicationResult = parallelMatrixMultiplication(m1, m2, dim, threadCount);
			endTime = getTime(Tzp,Tp);

			if(i != 0){
				totalParallelRunTime += endTime - startTime;
			}
		}

		//Calculate the max difference between the two matrices
		double maxDifference = maxMatrixDifference(sequentialMultiplicationResult, parallelMultiplicationResult, dim);

		//Display results
		printf("Sequential time: %f\n", totalSequentialRunTime / numTimesToRun);
		printf("Parallel time: %f\n", totalParallelRunTime / numTimesToRun);
		printf("Speedup: %f\n", totalSequentialRunTime / totalParallelRunTime);
		printf("Verifying... largest error between parallel and sequential multiplication %f\n", maxDifference);

		return 0;
	}
	//The input arguments were invalid
	else{
		printf("%s\n", usage);
		exit(1);
	}

	return 1;
}

/*
* Gets the current time in seconds
*/
double getTime(	struct timezone Tzp, struct timeval Tp){
	int stat;

	stat = gettimeofday (&Tp, &Tzp);
	if (stat != 0){
	    printf("Error return from gettimeofday: %d",stat);
	    return -1;
	}
	return Tp.tv_sec + Tp.tv_usec*1.0e-6;
}