typedef struct StackElem{
	char value[256];
	struct StackElem *next;
} StackElem;

typedef struct Stack{
	StackElem *head; //Pointer to topmost element of stack
} Stack;

int size(Stack);
void push(Stack *, char*);
StackElem *pop(Stack*);
void printStack(Stack, int);