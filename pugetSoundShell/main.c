#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "shell.h"
#include "main.h"




int main(){
	Stack s;
	s.head = NULL;
	char inputStream[MAX_INPUT];

	//Print the message of the day
	printMOTD();

	//Prompt user for shell commands
	while(1){
		printf("psh>");
		fgets(inputStream, MAX_INPUT, stdin); //read in
		strtok(inputStream, "\n"); //remove whitespace and \n
		if(strcmp(inputStream, "\n") == 0){
			continue;
		}
		processCommand(inputStream, &s);
		printf("\n");
	}
}