all: menu.o stat.o main.c
	gcc -Wall -o wordstat main.c menu.o stat.o

menu.o: menu.c
	gcc -Wall -c menu.c

stat.o: stat.c
	gcc -Wall -c stat.c

clean: 
	rm -f *.o wordstat