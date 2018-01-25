

#ifndef _HASHSEP_H
#include "util.h"
#define NextPrime
#define MinTableSize 3
typedef int ElementType;
typedef unsigned int Index;
struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

#endif

struct ListNode
{
	ElementType element;
	Position Next;
};

typedef Position List;

struct HashTbl
{
	int TableSize;
	List *TheLists;
};

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
	{
		error("Table size is too small");
		return NULL;
	}

	/* Allocate table */
	H = malloc(sizeof(struct HashTbl));
	if(H == NULL)
		FatalError("Out of sapce");

	H->TableSize = NextPrime(TableSize);

	/* Allocate array of lsits */
	H->TheLists = malloc(sizeof(List) * H->TableSize);
	if(H->TheLists == NULL)
		FatalError("Out of sapce");

	/* Allocate list header */
	H->TheLists = malloc(H->TableSize * sizeof(struct ListNode));
	if(H->TheLists == NULL)
		FatalError("Out of sapce");
	for(i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i]->Next = NULL;
	}

	return H;
}


