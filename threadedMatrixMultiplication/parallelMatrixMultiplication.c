#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "parallelMatrixMultiplication.h"
#include "matrixMultiplication.h"

/*
* Takes in two matrices and spawns off thread to calculate their product in parallel
* @param m1 one of the operand matrices
* @param m2 the other operand matrice
* @param dim the dimension of the matrices (all matrices are assumed to be square)
* @param threadCount the number of threads to spawn off
* @return the result of multiplying m1 * m2
*/
int **parallelMatrixMultiplication(int **m1, int **m2, int dim, int threadCount){
	//allocate space for storing N threads
    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t) * threadCount);
    //allocate space for result matrix
	int **result = mallocMatrix(dim, dim); 

	//Check to make sure we can split up the work properly
	//Work between threads is split row wise. So there can't be more threads than rows
	if(dim < threadCount){
		printf("Sorry, there must be atleast as many rows in the matrix as threads\n");
		exit(1);
	}

	//prepare threads
	long i;
	thread_args *args = (thread_args *) malloc(sizeof(thread_args) * threadCount);
	for (i=0; i<threadCount; i++)
	{
	    //prepare arguments for a thread
	    args[i].m1 = m1;
	    args[i].m2 = m2;
	    args[i].dim = dim;
	    args[i].result = result;
	    args[i].startResultRow = i*dim/threadCount;
	    args[i].endResultRow = (i+1)*dim/threadCount;

	    //fire off a thread
	    pthread_create(&threads[i], NULL, threadMatrixMultiplication, &args[i]);
	}


	//wait for all threads to finish
	for (i=0; i<threadCount; i++){
	    pthread_join(threads[i], NULL);
	}

	free(threads);
	free(args);
	return result;
}

/*
* Perform multiplies two matrices together and stores result in a global matrix 
* @params args a struct with the args for the method
*/
void *threadMatrixMultiplication(void *args){
	thread_args *params = (thread_args*)args;

	int **partialResult = mallocMatrix(params->endResultRow - params->startResultRow, params->dim);
	partialResult = matrixMultiplication(params->m1, params->m2, params->startResultRow, params->endResultRow, params->dim);

	int i, j;
	//Copy the threads calculated partial result into the final result matrix
	for(i = 0; i < params->endResultRow - params->startResultRow; i++){
		for(j=0; j<params->dim; j++){
			params->result[i+params->startResultRow][j] = partialResult[i][j];
		}
	}
	
	free(partialResult);
	return NULL;
}