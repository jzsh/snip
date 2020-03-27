#include <stdlib.h>
#include "arraylist.h"

int itemcmp(void *a, void *b);

int main()
{
    array_list_t *list = array_list_new(NULL);

    char *name = malloc(32);
    strcpy(name, "Zhangsan");
    array_list_add(list, name);
    array_list_add(list, "Lisi");
    array_list_add(list, "Wangwu");

//     free(name);
    array_list_rm(list, "Lisi");
    for(int i = 0; i < list->count; i++) {
        printf("%s\n", (char *)list->data[i]);
    }

    array_list_free(&list);
    list_foreach(list) {
        printf("%s\n", (char *)list->data[i]);
    }


    /** order list */

    bool inserted;
    list = array_list_new(NULL);
    array_list_insert_unique_ord(list, "Zhangsan", itemcmp, &inserted);
    array_list_insert_unique_ord(list, "Lisi", itemcmp, &inserted);
    array_list_insert_unique_ord(list, "Wangwu", itemcmp, &inserted);
    array_list_insert_unique_ord(list, "Xiaoliu", itemcmp, &inserted);
    list_foreach(list) {
        printf("%s\n", (char *)list->data[i]);
    }

}

int itemcmp(void *a, void *b)
{
    return strcmp(a, b);
}
