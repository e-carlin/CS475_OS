#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "stack.h"

double calculate(char *input){
	Stack s;
	s.root = NULL;
	char *token = strtok(input, " \n");

	while(token != NULL){
		//TODO: handle bad user input
		printf("token: \'%s\'\n", token);
		push(&s, atof(token));
		token = strtok(NULL, " \n");
	}
	return 666.666;
}