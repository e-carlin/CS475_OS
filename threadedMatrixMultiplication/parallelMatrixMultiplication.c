#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "parallelMatrixMultiplication.h"
#include "matrixMultiplication.h"

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


	// //wait for all threads to finish
	for (i=0; i<threadCount; i++){
	    pthread_join(threads[i], NULL);
	}



	// //TODO: Perform parallel multiplication
	// int **partialResult = mallocMatrix(1, dim);
	// int i;
	// for(i=0; i<dim; i++){
	// 	partialResult = matrixMultiplication(m1, m2, i, i+1, dim);
	// 	result[i] = partialResult[0];
	// }
	// free(partialResult);

	return result;
}

void *threadMatrixMultiplication(void *args){
	thread_args *params = (thread_args*)args;

	int **partialResult = mallocMatrix(params->endResultRow - params->startResultRow, params->dim);
	partialResult = matrixMultiplication(params->m1, params->m2, params->startResultRow, params->endResultRow, params->dim);
	printf("++++++ printing +++++\n");
	printMatrix(partialResult, params->endResultRow - params->startResultRow, params->dim);
	printf("++++++++++++++++++++++\n");


	int i, j;
	for(i=params->startResultRow; i<params->endResultRow; i++){
		for(j=0; j<params->dim; j++){
			printf("%d ",partialResult[i][j]);
		}
		printf("\n");
	}
	params->result[0][0] = 69;
	free(partialResult);
	return NULL;
}