#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "paras.h"

void InsertionSort(ElementType A[], int ArrSize)
{
	int j, p;
	ElementType inser;

	for(p = 1; p < ArrSize; p++) {
		inser = A[p]; /* insert A[p] to A[0 ~ p-1]*/
		for(j = p; j > 0 && A[j-1] > inser; j--)
			A[j] = A[j-1];
		A[j] = inser;
	}
}

void ShellSort(ElementType A[], int ArrSize)
{
	int i, j, increment;

	ElementType tmp;
	for(increment = ArrSize/2; increment > 0; increment /=2) {
		for(i = increment; i < ArrSize; i++) {
			tmp = A[i];
			for(j = i; j >= increment; j -= increment)
				if(tmp < A[j - increment])
					A[j] = A[j - increment];
				else
					break;
			A[j] = tmp;
		}
	}
}

void BubleSort(ElementType A[], int ArrSize)
{
	int i, j, tmp;

	for(i = 0; i < ArrSize -1; i++) {
		for(j = ArrSize - 1; j > i; j--) {
			if(A[j] < A[j - 1]) {
				tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
			}
		}
	}
}

int comp(const void *elem1, const void *elem2)
{
	int f = *((int *)elem1);
	int s = *((int *)elem2);
	if(f > s) return 1;
	if(f < s) return -1;
	return 0;
}

void BuildinSort(ElementType A[], int ArrSize)
{
	qsort(A, ArrSize, sizeof(A[0]), comp);
}

void SelectSort(ElementType A[], int ArrSize)
{
	int i, j, MinIndex;

	for(i = 0; i < ArrSize; i++) {
		MinIndex = i;
		/* find the position of min */
		for(j = i + 1; j < ArrSize; j++) {
			if(A[j] < A[MinIndex])
				MinIndex = j;
		}
		/* exchange min to positon i */
		if(MinIndex != i) {
			int tmp = A[i];
			A[i] = A[MinIndex];
			A[MinIndex] = tmp;
		}
	}
}


/* Return median of Left, Cernter, Right
 * Order these and hide the pivot
 */
void inline swap(void *elem1, void *elem2)
{
	int tmp;
	tmp = *(int *)elem1;
	*(int *)elem1 = *(int *)elem2;
	*(int *)elem2 = tmp;
}
ElementType Median3(ElementType A[], int left, int right)
{
	int center = (left + right) / 2;
	if(A[left] > A[center]) swap(&A[left], &A[center]);
	if(A[left] > A[right]) swap(&A[left], &A[right]);
	if(A[center] > A[right]) swap(&A[center], &A[right]);
	/* invarian : A[left] < A[center] < A[right] */
	swap(&A[center], &A[right - 1]); /* Hide pivot */
	return A[right - 1];
}

#define Cutoff (3)
void Qsort(ElementType A[], int left, int right)
{
	int i, j;
	ElementType pivot;

	if(left + Cutoff <= right) {
		pivot = Median3(A, left, right);
		i = left; j = right - 1;
		for(;;)
		{
			while(A[++i] < pivot){}
			while(A[--j] > pivot){}
			if(i < j)
				swap(&A[i], &A[j]);
			else
				break;
		}
		swap(&A[i], &A[right - 1]); /* restore pivot */
		Qsort(A, left, i - 1);
		Qsort(A, i + 1, right);
	}
	else /* Do an insertion sort on the subarray */
		InsertionSort(A + left, right - left + 1);
}
void QuickSort(ElementType A[], int ArrSize)
{
	Qsort(A, 0, ArrSize - 1);
}

void qsort2(int a[], int left,int right)
{
	int i,j,t,pivot;
	if(left > right)
	   return;

	pivot = a[left]; //pivot中存的就是基准数
	i = left;
	j = right;
	while(i != j)
	{
		//顺序很重要，要先从右边开始找
		while(a[j]>=pivot && i<j)
			j--;
		//再找右边的
		while(a[i]<=pivot && i<j)
			i++;
		//交换两个数在数组中的位置
		if(i<j)
		{
			t=a[i];
			a[i]=a[j];
			a[j]=t;
		}
	}
	//最终将基准数归位
	a[left]=a[i];
	a[i]=pivot;

	qsort2(a, left,i-1);//继续处理左边的，这里是一个递归的过程
	qsort2(a, i+1,right);//继续处理右边的 ，这里是一个递归的过程
}

void QuickSort2(ElementType A[], int ArrSize)
{
	qsort2(A, 0, ArrSize-1);
}

void BucketSort(ElementType A[], int ArrSize)
{
	int i, j;
	ElementType BuketArray[MAX];
	memset(BuketArray, 0, sizeof(int)*MAX);
	for(i = 0; i < ArrSize; i++)
	{
		BuketArray[A[i]]++;
	}
	j = 0;
	for(i = 0; i < MAX; i++)
	{
		while(BuketArray[i])
		{
			A[j] = i;
			BuketArray[i]--;
			j++;
		}
	}
}
