#Threaded Matrix Multiplication

Evan Carlin
3/34/2017

A program to compare execution time  
of matrix multiplication between serial  
vs. threaded execution.

To make:
	$ make all

To run:
	$ ./calculator

To clean:
	$ make clean

Notes:
This was compiled on the provided 64-Bit Ubuntu  
image using gcc. 

Areas for improvement:  
The threaded version could use many optimizations.  
A glaring one is that each partial solution is placed  
in its own matrix. This means that a new matrix must  
be allocated and subsequently freed. Likewise, all of  
the partial matrices must the be copied to the final  
matrix. To optimize the partial results could be placed  
directly in the final result matrix as they are calculated  
skipping the intermediate matrix. 
