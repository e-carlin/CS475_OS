/*
* @author Evan Carlin
* Reads in equations in Reverse Polish Notation
* and calculates the result. Operators and operands
* should be separated by space, tab, or newline
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h" //works fine
#include "rpn.h"
// #include "stack.h" //compilation error

#define MAX_INPUT 100

int main(){
	char input[MAX_INPUT];
	char runAgain = 'y';

	do{
		//Collect input
		printf("Enter an equation in RPN:\n");
		fgets(input, MAX_INPUT, stdin);

		//Calculate and show result
		StackElem *result = calculate(input);
		printf("Result = %f\n\n", result->value);
		//Free the result mem
		free(result);

		//Prompt user to calculate another equation
		printf("Evaluate another (y/n): ");
		scanf("%c", &runAgain);
		getchar(); //Clear \n from stdin
		printf("\n");
	}while(runAgain == 'y');

	printf("Exiting...\n");
	return 0;
}