#define bool unsigned char
#define true 1
#define false 0


typedef struct node{	//节点结构
    void *data;
    struct node *next;
} Node;

typedef struct {		//链表结构
    struct node *head;
    struct node *tail;
    long len;
} List;


// 初始化
void list_init(List *list);
// 销毁
void list_destroy(List *list, void (*destroy)(void *));
// 插入
void  list_insert(List *list, void *data);
// 头插法
void  list_insert_at_head(List *list, void *data);
// 随插法
void  list_insert_at_index(List *list, void *data, long index);
// 尾插法
void  list_insert_at_tail(List *list, void *data);
// 删除
void *list_delete(List *list, void *key, int (*compare)(const void *, const void *));
// 搜索
void *list_search(List *list, void *key, int (*compare)(const void *, const void *));
// 排序
void list_sort(List *list, int (*compare)(const void *, const void *));
// 遍历
void  list_traverse(List *list, void (*handle)(void *));
// 逆序
void list_reverse(List *list);
// 求长度
long  get_lenth(List *list);
// 获取链表节点
void *list_get_element(List *list, int index);
// 判断空链表
bool is_empty(List *list);


