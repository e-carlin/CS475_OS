/*
* @author Evan Carlin
* Starts the Puget Sound Shell
* Collects user input and passes it off to
* be processed by the shell.
*/
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "shell.h"

/*
* Prompts the user for input and passes
* the input to the shell API
*/
int main(){
	Stack s;
	s.head = NULL;
	char inputStream[MAX_INPUT_LEN];

	//Print the message of the day
	printMOTD();

	//Prompt user for shell commands
	while(1){
		printf("psh>");

		fgets(inputStream, MAX_INPUT_LEN, stdin); //read in
		strtok(inputStream, "\n"); //remove whitespace and \n

		if(strcmp(inputStream, "\n") == 0){
			continue;
		}
		processCommand(inputStream, &s);                
		printf("\n");
	}
}