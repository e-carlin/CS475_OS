all:  vmm.o main.c 
	gcc -Wall -o vmm main.c vmm.o


vmm.o: vmm.c
	gcc -Wall -c vmm.c

clean: 
	rm -f *.o vmm