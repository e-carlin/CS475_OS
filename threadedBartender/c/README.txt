Evan Carlin  
4/7/2017 


A threaded implementation of a bar in C.  
Only 2 people are allowed in the bar
at any time, the bartender and one 
customer. The bartender and each customer
are in their own threads.

This program was used to gain comfort
writing larger threaded programs and 
using semaphores.

To make:
	$ make all

To run:
	$ ./theBar <num customers>

To clean:
	$ make clean

Notes:
This was compiled on the provided 64-Bit Ubuntu  
image using gcc.