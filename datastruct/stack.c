#include <stdio.h>

#ifndef _STACK_H
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack s);
Stack CreateStack(void);


int IsEmpty(Stack s)
{
	return s->next == NULL;
}

Stack CreateStack(void)
{
	Stack s;
	s = malloc(sizeof(Node));
	if(s == NULL)
	{
		FatalError("Out of memory");
	}
}

void main()
{
	
}
