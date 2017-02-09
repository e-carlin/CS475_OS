typedef struct StackElem{
	float value;
	struct StackElem *next;
} StackElem;

typedef struct Stack{
	StackElem *head; //Pointer to topmost element of stack
} Stack;

int size(Stack);
void push(Stack *, float);
StackElem *pop(Stack*);
void printStack(Stack);