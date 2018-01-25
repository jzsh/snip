#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>
#include "sort.h"
#include "util.h"
#include "paras.h"

void pr_array(int A[], int length)
{
	int i;
	static int flag = 0;
	static int A1[N];

	if(flag == 1) {
		for(i = 0; i < length; i++) {
			if(A1[i] != A[i]) {
				info("Error sorted");
				flag = 0;
				break;
			}
		}
	}
	if(flag == 0) {
		for(i = 0; i < length; i++) {
			printf("%d, ", A[i]);
			A1[i] = A[i];
		}
		printf("\n");
		flag = 1;
	}
}

void gen_array(int A[], int size)
{
	int i;
	for(i = 0; i < size; i++) {
		A[i] = rand() % MAX;
	}
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
	info("Method:%s, \t Time:%lf",
			sort_method->name, timer_stop(sort_method->name));
	pr_array(array, size);
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
	};

	int A[N];

	gen_array(A, N);
	for(i = 0; i < sizeof(sort_methods)/sizeof(sort_methods[0]); i++) {
		test_sort(A, N, &sort_methods[i]);
	}
	return 0;
}


