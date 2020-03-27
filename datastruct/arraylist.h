/** @brief Header of arraylist
 *  @file arraylist.h
 *  @author Jiangzhe.Guo
 *  @version 0.1
 *  @date 17-Sep-2018
 */

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
/**
 * @defgroup logger Sysrepo Logger
 * @ingroup common
 * @{
 */
typedef void (array_list_free_fn) (void *data);

typedef struct array_list_s {
    void **data;    /**< Array of elements store in list */
    size_t count;   /**< Count of elements in the list */
    array_list_free_fn *free_fn; /**< free function ? */

    /* private */
    size_t _size;   /**< internel current allocate size of the list */
} array_list_t;

array_list_t *array_list_new(array_list_free_fn *free_fn);
void array_list_free(array_list_t **list);
/**
 * @brief Adds a new element at the end of the list.
 *
 * @note O(1).
 *
 * @param[in] list Pointer to the list structure.
 * @param[in] item Item to be added, the memory is maintained by user
 *
 * @return Error code (SR_ERR_OK on success).
 */
int array_list_add(array_list_t *list, void *item);
int array_list_rm_at(array_list_t *list, size_t index);
int array_list_rm(array_list_t *list, void *item);
int array_list_insert_unique_ord(array_list_t *list, void *item, int (*cmp) (void *, void*), bool *inserted);

#define list_foreach(list) \
    for(int i = 0; list && i < (list)->count; i++)

/**@} logger */
