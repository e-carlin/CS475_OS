all: matrixMultiplication.o sequentialMatrixMultiplication.o parallelMatrixMultiplication.o main.c
	gcc -Wall -g -o mmm main.c sequentialMatrixMultiplication.o parallelMatrixMultiplication.o matrixMultiplication.o -lpthread

parallelMatrixMultiplication.o: matrixMultiplication.o parallelMatrixMultiplication.c
	gcc -Wall -c parallelMatrixMultiplication.c -lpthread

sequentialMatrixMultiplication.o: matrixMultiplication.o sequentialMatrixMultiplication.c
	gcc -Wall -c sequentialMatrixMultiplication.c

matrixMultiplication.o: matrixMultiplication.c
	gcc -Wall -c matrixMultiplication.c

clean:
	rm -f *.o mmm
