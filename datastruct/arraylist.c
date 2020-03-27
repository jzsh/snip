
#include "arraylist.h"
#include "helper.h"

#define ARRAY_LIST_INIT_SIZE 32


array_list_t *array_list_new(array_list_free_fn *free_fn)
{
    array_list_t *list;
    list = (array_list_t *)calloc(1, sizeof(array_list_t));
    /* allocate initial space latter (when first add) */
    return list;
}

void array_list_free(array_list_t **list)
{
    if(list && *list != NULL) {
        if((*list)->free_fn)
            (*list)->free_fn((*list)->data);
        else
            free((*list)->data);
        free(*list);
        *list = NULL;
    }
}

int array_list_add(array_list_t *list, void *item)
{
    void **tmp = NULL;

    if(!list || !item)
        return 1;
    if(list->_size == 0) {
        list->data = calloc(ARRAY_LIST_INIT_SIZE, sizeof(*list->data));
        if(list->data == NULL) {
            fprintf(stderr, "can not calloc space\n");
            return 1;
        }

        list->_size = ARRAY_LIST_INIT_SIZE;
    } else if(list->_size == list->count) {
        /* double space */
        tmp = realloc(list->data, (list->_size * 2) * sizeof(*list->data));
        if(tmp == NULL) {
            fprintf(stderr, "can not calloc space\n");
            return 1;
        }
        list->data = tmp;
        list->_size <<= 1;
    }

    list->data[list->count] = item;
    list->count++;

    return 0;
}

int array_list_rm_at(array_list_t *list, size_t index)
{
    CHECK_NULL_ARG(list);

    if (index > list->count - 1) {
        DPRINT("Index %zu out of bounds of the list (0 - %zu)", index, list->count - 1);
        return ERR_INVAL_ARG;
    }

    if (index == (list->count - 1)) {
        /* just "remove" the last item */
        list->count--;
    } else {
        /* move the remaining items forward */
        memmove(&list->data[index], &list->data[index + 1], (list->count - index - 1) * sizeof(*list->data));
        list->count--;
    }

    return ERR_OK;
}

int array_list_rm(array_list_t *list, void *item)
{
    if(!list || !item)
        return 1;

    if (item == list->data[list->count - 1]) {
        /* just "remove" the last item */
        list->count--;
        return 0;
    }

    for (size_t i = 0; i < (list->count - 1); i++) {
        /* find and remove matching item */
        if (item == list->data[i]) {
            return array_list_rm_at(list, i);
        }
    }

    return ERR_NOT_FOUND;
}

int array_list_insert_unique_ord(array_list_t *list, void *item, int (*cmp) (void *, void*), bool *inserted)
{
    CHECK_NULL_ARG3(list, item, cmp);
    void **tmp = NULL;
    int rc = ERR_OK;
    int res = 0;
    size_t position = 0;
    /* find position */
    for (; position < list->count; position++) {
        res = cmp(item, list->data[position]);
        if (0 == res) {
            if (NULL != inserted) {
                *inserted = false;
            }
            return rc;
        } else if (res < 0) {
            break;
        } else {
            continue;
        }
    }

    /* allocation */
    if (0 == list->_size) {
        /* allocate initial space */
        list->data = calloc(ARRAY_LIST_INIT_SIZE, sizeof(*list->data));
        CHECK_NULL_NOMEM_RETURN(list->data);
        list->_size = ARRAY_LIST_INIT_SIZE;
    } else if (list->_size == list->count) {
        /* enlarge the space */
        tmp = realloc(list->data,  (list->_size << 1) * sizeof(*list->data));
        CHECK_NULL_NOMEM_RETURN(tmp);
        list->data = tmp;
        list->_size <<= 1;
    }

    /* memove */
    if (position < list->count) {
        memmove(&list->data[position+1],
                &list->data[position],
                (list->count-position) * sizeof(*list->data));
    }

    /* insert element*/
    list->data[position] = item;
    list->count++;

    if (NULL != inserted) {
        *inserted = true;
    }

    return rc;
}

