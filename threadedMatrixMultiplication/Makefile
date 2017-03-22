all: matrixMultiplication.o main.c
	gcc -Wall -g -o mmm main.c matrixMultiplication.o -lpthread

matrixMultiplication.o: matrixMultiplication.c
	gcc -Wall -c matrixMultiplication.c

clean:
	rm -f *.o mmm
