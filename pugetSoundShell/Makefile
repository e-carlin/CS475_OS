all: shell.o main.c
	gcc -Wall -o psh main.c shell.o

shell.o: shell.c shell.h
	gcc -Wall -c shell.c
        
clean:
	rm -f *.o psh
