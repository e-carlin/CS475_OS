/*
* @author Evan Carlin
*
*/

#include <stdio.h>
#include "rpn.h"

#define MAX_INPUT 100

int main(){
	char input[MAX_INPUT];

	//Collect input
	printf("Enter an equation in RPN:\n");
	fgets(input, MAX_INPUT, stdin);

	double result = calculate(input);
	printf("%f\n", result);

	return 0;
}