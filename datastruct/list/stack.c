/*
	Stack implemented by array
*/
#include <stdlib.h>
#include <stdio.h>

#define MinStackSize 3
#define ElementType char
#define EmptyTOS -1

struct StackRecord;
typedef struct StackRecord *Stack;

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyTOS;
}

int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity;
}

Stack CreateStack(int MaxElements)
{
	Stack S;
	if(MaxElements < MinStackSize)
		printf("Stack size is too small\n");

	S = malloc(sizeof(struct StackRecord));
	if(S == NULL)
		printf("Out of space!!!\n");

	S->Array = malloc(sizeof(ElementType) * MaxElements);
	if(S == NULL)
		printf("Out of sapce!!!\n");
	S->Capacity = MaxElements;
	MakeEmpty(S);

	return S;
}

void DisposeStack(Stack S)
{
	if(S != NULL)
	{
		free(S->Array);
		free(S);
	}
}

void Push(Stack S, ElementType X)
{
	if(IsFull(S))
		error("Cannot push to full stack");
	else
		S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[S->TopOfStack];
	error("Empty stack");
	return 0; /* Return value used to avoid warning */
}

ElementType Pop(Stack S)
{
	if(IsEmpty(S))
	{
		error("Cannot pop out of empty stack");
		return 0;
	}
	else
		return S->Array[S->TopOfStack--];
}

char* reverseWords(char* s)
{
	Stack S;
	int i = 0;

	if(s == NULL)
		return s;

	S = CreateStack(128);
	char *p = s;
	while(*p != '\0')
	{
		if(*p != ' ')
		{
			Push(S, *p);
		}
		else
		{
			while(!IsEmpty(S))
			{
				s[i++] = Pop(S);
			}
			i++;
		}
		p++;
	}
	while(!IsEmpty(S))
	{
		s[i++] = Pop(S);
	}
	return s;
}

void main()
{
	char s[] = "abcdefghijklmn opq rstuvwxyz";
	printf("origin:\n%s\n", s);
	printf("reverse:\n%s\n", reverseWords(s));
}



