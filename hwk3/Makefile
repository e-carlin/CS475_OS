all: main.c rpn.h rpn.o
	gcc -Wall -o calculator main.c rpn.o stack.o

rpn.o: rpn.c rpn.h stack.o
	gcc -Wall -c rpn.c

stack.o: stack.c stack.h
	gcc -Wall -c stack.c

clean:
	rm -f *.o calculator

