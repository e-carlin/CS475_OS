all: stack.o shell.o main.c
	gcc -Wall -o psh main.c stack.o shell.o

shell.o: shell.c stack.o
	gcc -Wall -c shell.c

stack.o: stack.c
	gcc -Wall -c stack.c
        
clean:
	rm -f *.o psh
