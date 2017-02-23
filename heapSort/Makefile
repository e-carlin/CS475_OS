all: heap.o main.c
	gcc -Wall -o heapsort main.c heap.o


heap.o: heap.c heap.h
	gcc -Wall -c heap.c

clean: 
	rm -f *.o heapsort