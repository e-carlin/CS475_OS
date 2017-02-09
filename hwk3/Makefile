all: stack.o rpn.o main.c
	gcc -Wall -o calculator main.c stack.o rpn.o

rpn.o: rpn.c stack.o
	gcc -Wall -c rpn.c stack.o

stack.o: stack.c
	gcc -Wall -c stack.c

clean:
	rm -f *.o calculator

