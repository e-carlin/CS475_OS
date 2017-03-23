all: matrixMultiplication.o sequentialMatrixMultiplication.o main.c
	gcc -Wall -g -o mmm main.c sequentialMatrixMultiplication.o matrixMultiplication.o -lpthread

sequentialMatrixMultiplication.o: matrixMultiplication.o sequentialMatrixMultiplication.c
		gcc -Wall -c sequentialMatrixMultiplication.c

matrixMultiplication.o: matrixMultiplication.c
	gcc -Wall -c matrixMultiplication.c

clean:
	rm -f *.o mmm
