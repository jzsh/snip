#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int a[], int len, int key)
{
    int lo = 0;
    int hi = len - 1;
    int mid;
    while(lo <= hi) {
        mid = (lo + hi) / 2;
        if(key < a[mid])
            hi = mid - 1;
        else if(key > a[mid])
            lo = mid + 1;
        else
            return mid;
    }
    return -1;
}

int comp(const void *elem1, const void *elem2)
{
    int f = *((int *)elem1);
    int s = *((int *)elem2);
    if(f > s) return 1;
    if(f < s) return -1;
    return 0;
}

int main()
{
    int i;
    int N = 50;
    int a[N];
	unsigned int cur = (unsigned int)time(NULL);

    for(i = 0; i < N; i++)
    {
        a[i] = rand_r(&cur) % 100;
    }
    qsort(a, N, sizeof(a[0]), comp);

    for(i = 0; i < N; i++)
    {
    	printf("%d,", a[i]);
    }
    printf("\n");

    int f;
    scanf("%d", &f);
    int d = binarySearch(a, N, f);
    if(d != -1)
        printf("found:a[%d]=%d\n", d, a[d]);
    else
        printf("not found\n");
}



