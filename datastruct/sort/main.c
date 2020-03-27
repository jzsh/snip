#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>
#include <time.h>

#include <sort.h>
#include <util.h>


void print_array(int A[], int length)
{
	int i;
	for(i = 0; i < length; i++) {
		printf("%d,", A[i]);
	}
	printf("\n");
}

int is_sort_failed(int A[], int length)
{
	int i;
	for(i = 1; i < length; i++) {
		if(A[i] < A[i - 1]) {
			/* sort failed */
			return 1;
		}
	}
	return 0;
}

void gen_array(int A[], int size)
{
	int i;
	printf("Origin array:\n");
    srand(time(NULL));
	for(i = 0; i < size; i++) {
		A[i] = rand() % MAX;
		printf("%d,", A[i]);
	}
	printf("\n");
}

void copy_array(int A[], int size, int A2[])
{
	int i;
	for(i = 0; i < size; i++) {
		A2[i] = A[i];
	}
}

struct sortMethods {
	const char *name;
	void (*sort)(ElementType A[], int size); 
};

void test_sort(ElementType A[], int size, struct sortMethods *sort_method)
{
	int array[size];

	copy_array(A, size, array);
	timer_start(sort_method->name);
	(sort_method->sort)(array, sizeof(array)/sizeof(array[0]));

	if(is_sort_failed(array, size) == 1) {
		printf("Method:%s Failed!\n", sort_method->name);
		print_array(A, size);
		print_array(array, size);
	} else {
		info("Method:%s, \t Time:%lf",
				sort_method->name, timer_stop(sort_method->name));
	}
}

int main()
{
	int i;
	struct sortMethods sort_methods[] = {
						{.name = "BuildinSort", .sort = BuildinSort},
						{.name = "BubleSort", .sort = BubleSort},
						{.name = "InsertionSort", .sort = InsertionSort},
						{.name = "ShellSort", .sort = ShellSort},
						{.name = "SelectSort", .sort = SelectSort},
						{.name = "QuickSort", .sort = QuickSort},
						{.name = "QuickSort2", .sort = QuickSort2},
						{.name = "BucketSort", .sort = BucketSort},
						{.name = "MergeSort", .sort = MergeSort},
						{.name = "HeapSort", .sort = HeapSort},
						{.name = "RadixSort", .sort = RadixSort},
	};

	int A[N];

	gen_array(A, N);
	for(i = 0; i < sizeof(sort_methods)/sizeof(sort_methods[0]); i++) {
		test_sort(A, N, &sort_methods[i]);
	}
	return 0;
}


