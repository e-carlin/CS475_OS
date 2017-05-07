all:  vmm.o queue.o newqueue.o main.c 
	gcc -Wall -o vmm main.c vmm.o queue.o newqueue.o -lm


vmm.o: vmm.c 
	gcc -Wall -c vmm.c 

queue.o: queue.c
	gcc -Wall -c queue.c

newqueue.o: newqueue.c
	gcc -Wall -c newqueue.c

clean: 
	rm -f *.o vmm