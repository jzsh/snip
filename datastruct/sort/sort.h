#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#define N 10000
#define MIN 0
#define MAX (2*N)
#define ElementType int


void BuildinSort(ElementType A[], int ArrSize);
void InsertionSort(ElementType A[], int ArrSize);
void ShellSort(ElementType A[], int ArrSize);
void BubleSort(ElementType A[], int ArrSize);
void SelectSort(ElementType A[], int ArrSize);
void QuickSort(ElementType A[], int ArrSize);
void QuickSort2(ElementType A[], int ArrSize);
void BucketSort(ElementType A[], int ArrSize);
void MergeSort(ElementType A[], int ArrSize);
void HeapSort(ElementType A[], int ArrSize);
void RadixSort(ElementType A[], int ArrSize);
#endif
