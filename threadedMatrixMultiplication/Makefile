all: matrixMultiplication.o serialMatrixMultiplication.o main.c
	gcc -Wall -g -o mmm main.c serialMatrixMultiplication.o matrixMultiplication.o -lpthread

serialMatrixMultiplication.o: matrixMultiplication.o serialMatrixMultiplication.c
		gcc -Wall -c serialMatrixMultiplication.c

matrixMultiplication.o: matrixMultiplication.c
	gcc -Wall -c matrixMultiplication.c

clean:
	rm -f *.o mmm
