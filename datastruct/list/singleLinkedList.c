/**
 * single linked list without head
 * reference: http://www.cnblogs.com/gylei/archive/2013/03/16/2963546.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include <assert.h>

#include "singleLinkedList.h"

void list_init(List *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

bool is_empty(List *list)
{
    return (list->head == NULL);
}

// 把用户传递过来的数据打包为一个链表节点
static struct node *make_node(void *data)
{
    struct node *n;

    n = malloc(sizeof(struct node));
    assert(n != NULL);

    n->next = NULL;
    n->data = data;

    return n;
}

void list_insert_at_head(List *list, void *data)    //头插法
{
    struct node *n;
    n = make_node(data);

    if(list->head == NULL){ //如果是空链表
        list->head = n;
        list->tail = n;
    }
    else{                   //如果不是非空链表
        n->next = list->head;
        list->head = n;
    }
    list->len++;
}

void list_insert_at_tail(List *list, void *data)    //尾插法
{
    struct node *n;
    n = make_node(data);

    if(list->head == NULL){    //如果是空链表
        list->head = n;
        list->tail = n;
        n->next = NULL;
    }
    else{                      //如果不是非空链表
        list->tail->next = n;
        list->tail = n;
        n->next = NULL;
    }
    list->len++;
}

void list_insert_at_index(List *list, void *data, long index)
{
    long i = 1; //从1开始算
    struct node *p, *n;

    p = list->head;

    while(p && i < index){
        p = p->next;
        i++;
    }

    if(p){ //如果链表遍历完了，计数i还没到index，说明第index个节点不存在。
        n = make_node(data);
        n->next = p->next;
        p->next = n;
        list->len++;
    }
}

void list_insert(List *list, void *data)    //默认采用尾插法
{
    list_insert_at_tail(list, data);
}

//以key为删除关键词，compare为节点数据比较机制，由用户自己编写
void *list_delete(List *list, void *key,
            int (*compare)(const void *, const void *))
{
    void *data;
    struct node *n, *t;
    n = list->head;

    if(!compare(n->data, key)){    //如果要删除的节点为首节点
        printf("list_delete\n");
        t = n;
        data = n->data;
        list->head = n->next;
        free(t);
        list->len--;
        return data;
    }

    while(n->next != NULL){        //遍历查找符合条件的节点，删除之
        if(compare(n->next->data, key) == 0){    //只删除第一个符合条件的节点。
            t = n->next;
            if(n->next == list->tail){
                list->tail = n;
            }
            n->next = n->next->next;
            data = t->data;
            free(t);
            list->len--;
            return data;    //把删除的数据返回给用户，供用户后续的处理使用。
        }
        n = n->next;
    }
    return NULL;    //没找到匹配的节点，返回NULL
}

// handle()为节点遍历策略,由用户自己编写
void list_traverse(List *list, void (*handle)(void *)) 
{
    struct node *p;

    p = list->head;
    while(p){
        handle(p->data);
        p = p->next;
    }
}

void *list_search(List *list, void *key, int (*compare)(const void *, const void *))  //以key为搜索关键词，compare为节点数据比较机制，由用户自己编写
{
    struct node *n;
    n = list->head;

    while(n){
        if(!compare(n->data, key)){    //找到了，返回找到的数据
            return n->data;
        }
        n = n->next;
    }

    return NULL;    //找不到，返回NULL
}

// 链表的排序
static struct node * find_min_node(List *list,
        int (*compare)(const void *, const void *))    //找最小节点，链表排序用；以compare为比较机制，由用户自己编写
{
    struct node *min, *n;

    n = list->head;
    min = list->head;

    while(n) {
        if(compare(min->data, n->data) > 0) {
            min = n;
        }
        n = n->next;
    }
    return min;
}

static void delete_node(List *list, struct node *key)    //以节点数据key为关键词，删除匹配的节点，链表排序用；
{
    struct node *n;

    n = list->head;

    if(n == key){
        list->head = n->next;
        return;
    }

    while(n->next){
        if(n->next == key){
            if(key == list->tail){
                list->tail = n;
            }
            n->next = n->next->next;
            return;
        }
        n = n->next;
    }
}

static void insert_node(List *list, struct node *key)//以节点数据key为关键词，插入匹配的节点，链表排序用；
{
    if(list->head == NULL){
        list->head = key;
        list->tail = key;
    }else{
        list->tail->next = key;
        list->tail = key;
    }
}

void list_sort(List *list,
        int (*compare)(const void *, const void *))
{
    List tmp;
    struct node *n;

    list_init(&tmp);

    while(! is_empty(list)) {
        n = find_min_node(list, compare);
        delete_node(list, n);
        n->next = NULL;
        insert_node(&tmp, n);
    }
    list->head = tmp.head;
    list->tail = tmp.tail;
}

void list_reverse(List *list)
{
    struct node *prev = NULL, *next, *p = list->head;

    list->tail = list->head;    //tail指向head；第一次head到tail的倒置。
    while(p){
        next = p->next;
        if(!next){  //当p->next为最后一个节点时，让head指向p->next；最后一次tail到head的倒置。
            list->head = p;
        }

		/* 指向前一个结点 */
        p->next = prev;
		/* 备份当前节点为prev，作为其下一个节点的next（第一个节点为NULL，初始化时已定义） */
        prev = p; 

        p = next;
    }
}

long get_lenth(List *list)
{
    return (list->len);
}

void *list_get_element(List *list, int idx)
{
    int i = 0;
    struct node *n;
    n = list->head;

    while(n && i < idx){
        i ++;
        n = n->next;
    }

    if(n){
        return n->data;
    }

    return NULL;
}

// destroy为销毁链表时对节点数据的处理函数,由用户自己编写。传递NULL时表示不做处理
void list_destroy(List *list, void (*destroy)(void *))
{
    list->len = 0;
    struct node *n, *tmp;
    n = list->head;

    while(n){
        tmp = n->next;    //tmp只起一个记录n->next的功能，否则后面把n free掉之后，就找不到n->next了。
        if(destroy){  //传递用户自定义的数据处理函数，为0时不执行
           destroy(n->data);    //使用用户提供的destroy函数来释放用户的数据。
        }
        free(n);
        n = tmp;  //把n free掉之后，再把tmp给n，相当于把n->next给n,如此循环遍历链表，挨个删除。
    }
}

typedef struct test{
    int val1;
    float val2;
}test_t;

void handle(void *data)
{
    test_t *test = (test_t *)data;
    printf("val1:%d, val2:%f\n", test->val1, test->val2);
}

int compare_int(const void *s1, const void *s2)
{
    test_t *data1 = (test_t *)s1;
    int *data2 =(int *)s2;

    return (data1->val1 - *data2);
}

int compare_int_sort(const void *s1, const void *s2)
{
    test_t *data1 = (test_t *)s1;
    test_t *data2 = (test_t *)s2;

    return (data1->val1 - data2->val1);
}

void print(List *list)
{
    printf("list len = %ld\n", get_lenth(list));
    if(!is_empty(list)){
        //test list_reverse
        list_traverse(list, handle);
    }
    else{
        printf("\tthe list is empty\n");
    }
}

int main(void)
{
    List list;
    list_init(&list);
    test_t test1 = {10, 10.5};
    test_t test2 = {20, 20.5};
    test_t test3 = {30, 30.5};
    test_t test4 = {40, 40.5};
    test_t test5 = {50, 50.5};

    //test list_insert
    printf("------insert(_at_tail)----\n");
    list_insert(&list, &test1);
    list_insert(&list, &test2);
    list_insert(&list, &test3);
    print(&list);

    //test list_delete
    printf("------delete----\n");
    list_delete(&list, &test1.val1, compare_int);
    print(&list);

    //test list_insert_at_head
    printf("------insert_at_head----\n");
    list_insert_at_head(&list, &test4);
    print(&list);

    //test list_insert_at_index
    printf("------insert_at_index(2)----\n");
    list_insert_at_index(&list, &test5, 2);
    print(&list);

    //test list_reverse
    printf("------reverse----\n");
    list_reverse(&list);
    print(&list);

    //test list_search
    int key = 20;
    test_t *ret;
    printf("------search----\n");
    ret = list_search(&list, &key, compare_int);
    printf("%d:%f\n", ret->val1, ret->val2);
    key = 50;
    ret = list_search(&list, &key, compare_int);
    printf("%d:%f\n", ret->val1, ret->val2);

    //test list_get_element
    printf("------list_get_element----\n");
    ret = list_get_element(&list, 2);
    printf("%d:%f\n", ret->val1, ret->val2);
    ret = list_get_element(&list, 3);
    printf("%d:%f\n", ret->val1, ret->val2);

    //test list_sort
    printf("-----sort----\n");
    list_sort(&list, compare_int_sort);
    print(&list);

    //test list_destroy
    printf("-----destroy----\n");
    list_destroy(&list, NULL);

    return 0;
}

