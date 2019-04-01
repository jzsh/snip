#include <stdio.h>

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

int main()
{
    int i;
    int N = 50;
    int a[N];
    for(i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
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



