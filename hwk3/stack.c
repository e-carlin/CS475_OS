#include <stdlib.h>
#include <stdio.h> //TODO: Remove, just for testing
#include "stack.h"

/*
* Gets the current size of the stack
* @return the size of the stack
*/
int size(Stack s){
	int size = 0;

	StackElem *elem = s.head;
	while(elem != NULL){
		size++;
		elem = elem->next;
	}
	return size;
}

/*
* Push an element onto the stack
*/
void push(Stack *s, float value){
	//Stack is empty
	if(s->head == NULL){
		//Allocate space for new elem
		StackElem *elem = (StackElem *) malloc(sizeof(StackElem));
		
		//Assign fields
		elem->value = value;
		elem->next = NULL;

		//Set head of stack to be new elem
		s->head = elem;
	}
	else{
		//Allocate space for new elem
		StackElem *elem = (StackElem *) malloc(sizeof(StackElem));

		//Assign fields
		elem->value = value;
		elem->next = s->head;
		s->head = elem;
	}
}

StackElem *pop(Stack *s){
	StackElem *head = s->head;
	s->head = head->next;
	return head;
}


void printStack(Stack s){
	printf("*********** Printing stack **************\n");
	printf("Stack size is %d\n", size(s));
	StackElem *elem = s.head;
	while(elem != NULL){
		printf("%f -> ", elem->value);
		elem = elem->next;
	}
	printf("\n");
}