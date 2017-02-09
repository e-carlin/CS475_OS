/*
* Pareses a string in Reverse Polish Notation
* and calculates the result. Supports +, -, *, and /.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "rpn.h"

/*
* Parse input equation in RPN and calculate result
* @param input the input equation in RPN
* @return the head element which contains the reuslt
*/
StackElem *calculate(char *input){
	//Create empty stack for operators
	Stack s;
	s.head = NULL;

	//Get first token
	char *token = strtok(input, " \n\t");

	//Continue reading tokens
	while(token != NULL){
		//TODO: handle bad user input
		// and floats
		// and things like 12$4

		//Check if the token is a num
		if(isdigit(token[0])){
			//Add numbers to operands stack
			push(&s, atof(token));
		}
		//Check if the token is a valid operator
		else if(isValidOperator(token[0])){
			//We need atleast two elements to be able to perform an operation
			if(size(s) < 2){
				printf("Error: not enough operands to perform %s\n", token);
				exit(1);
			}
			//There are enough operands on the stack
			else{
				//Pop off top two operands
				StackElem *head = pop(&s);
				StackElem *next = pop(&s);

				//Perform operation
				float result = performOp(head->value, next->value, token[0]);
				
				//Free mem used by head and next
				free(head);
				free(next);

				//Push result onto stack
				push(&s, result);
			}
		}
		//Not a valid operator (+,-,*,/)
		else{
			printf("Error: operator %s unrecognized\n", token);
			exit(1);
		}

		//Get the next token
		token = strtok(NULL, " \n\t");
	}

	/**** Return result ****/

	//There is > 1 operands on the stack so the result is unclear
	if(size(s) > 1){
		printf("Not enough operators for number of operands\n");
		exit(1);
	}
	//Return the reuslt
	else{
		return pop(&s);
	}
}

int isValidOperator(char op){
	return (op == '+' ||
		op == '-' ||
		op == '*' ||
		op == '/') ? 1 : 0;
}

float performOp(float head, float next, char op){
	if(op == '+')
		return next + head;
	if(op == '-')
		return next - head;
	if(op == '*')
		return next * head;
	if(op == '/'){
		if(head == 0.0){
			printf("Error: division by 0\n");
			exit(1);
		}
		else
			return next / head;
	}
	return 666.666;
}
 