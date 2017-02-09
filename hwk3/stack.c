#include <stdlib.h>
#include <stdio.h> //TODO: Remove, just for testing
#include "stack.h"

/*
* Gets the current size of the stack
* @return the size of the stack
*/
int size(Stack s){
	return s.size;
}

/*
* Push an element onto the stack
*/
void push(Stack *s, float value){
	printf("In push\n");

	//Stack is empty
	if(s->root == NULL){
		printf("Adding first elem to stack\n");
		//Allocate space for new elem
		StackElem *elem = (StackElem *) malloc(sizeof(StackElem));
		
		//Assign fields
		elem->value = value;
		elem->next = NULL;

		//Set root of stack to be new elem
		s->root = elem;
	}
	else{
		printf("Stack is not empty, adding another elem\n");
		//Allocate space for new elem
		StackElem *elem = (StackElem *) malloc(sizeof(StackElem));

		//Assign fields
		elem->value = value;
		elem->next = s->root;
		s->root = elem;
	}
	printf("Done pushing\n");
}

float pop(Stack *s){
	return 666.666;
}
