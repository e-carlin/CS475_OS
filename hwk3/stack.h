typedef struct StackElem{
	float value;
	struct StackElem *next;
} StackElem;

typedef struct Stack{
	StackElem *root; //Pointer to topmost element of stack
	int size;
} Stack;

int size(Stack);
void push(Stack *, float);
float pop(Stack*);