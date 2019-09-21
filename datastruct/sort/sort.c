#include <stdlib.h>
#include <string.h>
#include "sort.h"


/* 插入法
 * */
void InsertionSort(ElementType A[], int ArrSize)
{
    int j, p;
    ElementType in; // num to be inserted

    for(p = 1; p < ArrSize; p++) {
        in = A[p]; /* 插入A[p]到已排序好的数组A[0 ~ p-1]中 */
        for(j = p; j > 0 && A[j-1] > in; j--)
            A[j] = A[j-1]; // right shift for in
        A[j] = in;
    }
}

/* 希尔排序是一种插入排序，又称缩小增量排序, 基于以下2点性质改进：
 * 1. 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率。
 * 2. 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位。
 * */
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

/* 冒泡排序
 * 每一趟, 把还未排序中的最小的值移动到数组前
 * 相邻两元素比较 */
void BubleSort(ElementType A[], int ArrSize)
{
    int i, j, tmp;

    for(i = 0; i < ArrSize - 1; i++) {
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

// 从未排序的序列中选择最小的元素，与放在第一个位置的元素交换
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
static void inline swap(void *elem1, void *elem2)
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
// 交换法
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
        // 當i,j指针重合时，交换此重合点与pivot元素
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

// 挖坑法
void qsort2(int a[], int left,int right)
{
    int i,j,pivot,index;
    if(left > right)
       return;

    i = left;
    j = right;
    pivot = a[left]; //pivot中存的就是基准数
    index = left;

    while(i < j)
    {
        // 1. 顺序很重要，要先从右边开始找, 找一个小于基准的数
        while(i < j) {
            if(a[j] < pivot) {
                a[index] = a[j];
                index = j;
                i++;
                break;
            }
            j--;
        }

        // 2. 再找左边的, 找一个大于基准的数
        while(i < j) {
            if(a[i] > pivot) {
                a[index] = a[i];
                index = i;
                j--;
                break;
            }
            i++;
        }

    }
    // 3. 最终将基准数归位
    a[index] = pivot;

    qsort2(a, left,index-1);//继续处理左边的，这里是一个递归的过程
    qsort2(a, index+1,right);//继续处理右边的 ，这里是一个递归的过程
}

void QuickSort2(ElementType A[], int ArrSize)
{
    qsort2(A, 0, ArrSize-1);
}

// 合并2个有序数组,分配一个临时空间，装a，b的结果，
// 最后，将合并结果拷贝到数组A，是否临时空间
void merge_array(int *a,int size_a,int *b, int size_b)
{
    int *tmp = malloc( (size_a+size_b)*sizeof(int) );
    int i,j,k;
    i=j=k=0;

    while(i<size_a && j<size_b) {
        tmp[k++] = (a[i]>b[j])?b[j++]:a[i++];
    }

    while(i<size_a) {

        tmp[k++]=a[i++];
    }

    while(j<size_b) {

        tmp[k++]=b[j++];
    }

    for (int p = 0; p < k; ++p)
    {
        a[p] = tmp[p];
    }

    free(tmp);
}

// 归并排序
void MergeSort(ElementType A[], int ArrSize)
{
    if(ArrSize > 1) {
        MergeSort(A, ArrSize/2);
        MergeSort(A + ArrSize/2, ArrSize - ArrSize/2);
        merge_array(A, ArrSize/2, A + ArrSize/2, ArrSize - ArrSize/2);
    }
}

/* 堆排序
完全二叉树： 除了最后一层之外的其他每一层都被完全填充，并且所有结点都保持向左对齐

         0
       /    \
      1     2
     / \   /  \
    3   4 5    6
左边子节点位置 = 当前父节点的两倍 + 1，右边子节点位置 = 当前父节点的两倍 + 2

a.将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;
b.将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;
c.重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，
反复执行调整+交换步骤，直到整个序列有序。
*/

void adjustHeap(ElementType A[], int i, int length)
{
    int tmp = A[i];
    for(int k=i*2+1; k < length; k=k*2+1/*子节点*/) {
        if(k+1 < length && A[k] < A[k+1]) // 如果左子结点小于右子结点，k指向右子结点
        {
            k++;
        }
        if(A[k] > tmp) { //如果子节点大于父节点，将子节点值赋给父节点
            A[i] = A[k];
            i = k; // 调整后，判断是否还满足大顶堆
        } else {
            break;
        }
    }
    A[i] = tmp;
}

void HeapSort(ElementType A[], int ArrSize)
{
    // 构建大顶堆
    for(int i = ArrSize/2 - 1; i>=0; i--) {
        // 从第一个非叶子结点(下标为ArrSize/2-1), 从下至上，从右至左调整结构
        adjustHeap(A, i, ArrSize);
    }

    // 交换堆顶元素与末尾元素, 调整堆结构
    for(int j=ArrSize-1; j > 0; j--) {
        swap(&A[0], &A[j]);
        adjustHeap(A, 0, j);
    }
}

// 桶排序
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
