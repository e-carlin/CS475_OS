int **parallelMatrixMultiplication(int **m1, int **m2, int dim, int threadCount);
void *threadMatrixMultiplication(void *args);

typedef struct thread_args{
	int **m1;
	int **m2;
	int **result;
	int startResultRow;
	int endResultRow;
	int dim;
} thread_args;