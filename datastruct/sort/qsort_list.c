#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
}node;

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

node *partion(node *head, node *end)
{
    node *p1, *p2;

    if(head == end || head->next == end )
        return head;

    p1 = head;
    p2 = head->next;
    int pivot = head->data;

    // p2走到末尾
    while(p2 != end) {
        // 大于基准值时，p1向前走一步，交换p1与p2的值
        if(p2->data < pivot) {
            p1 = p1->next;
            swap(&p1->data, &p2->data);
        }
        p2 = p2->next;
    }

    // 当有序时，不交换p1和key值
    if(p1 != head) {
        swap(&head->data, &p1->data);
    }
    return p1;
}

void quickSort(node *head, node *end)
{
    if(head == NULL)
        return;
    if(head == end || head->next == end)
        return;

    node *n = partion(head, end);
    quickSort(head, n);
    quickSort(n->next, end);
}

node *sortList(node *head)
{
    quickSort(head, NULL);
    return head;
}

void main()
{
    node a = {1, };
    node b = {4, };
    node c = {6, };
    node d = {2, };
    node e = {5, };
    node f = {7, };
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = NULL;

    sortList(&a);
    node *p = &a;

    while(p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");

}
