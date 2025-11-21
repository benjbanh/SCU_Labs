/**
 * Use a circular doubly linked list
 * have head or tail but itself does not hold data
 * All operations except destroyList, removeItem, findItem, and getItems are required to run in O(1) time.
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list
{
    int count;
    struct node *head;
    int (*compare)();
} LIST;

/**
 * return a pointer to a new list using compare as its comparison function, which may be NULL
 * O(1)
 */
LIST *createList(int (*compare)())
{
    LIST *list = malloc(sizeof(LIST));
    assert(list != NULL);
    list->count = 0;
    list->compare = compare;
    list->head = malloc(sizeof(NODE));
    assert(list->head != NULL);
    list->head->prev = list->head;
    list->head->next = list->head;
    return list;
}

/**
 * deallocate memory associated with the list pointed to by lp
 * O(n)
 */
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *curr = lp->head->next;
    NODE *next;
    while (curr != lp->head)
    {
        next = curr;
        free(curr);
        curr = next;
        curr = curr->next;
    }
    free(lp->head);
    free(lp);
}

/**
 * return the number of items in the list pointed to by lp
 * O(1)
 */
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

/**
 * return the number of items in the list pointed to by lp
 * O(n)
 */
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL);
    assert(item != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->prev = lp->head;
    new->next = lp->head->next;
    lp->head->next = new;
    lp->count++;
}

/**
 * add item as the last item in the list pointed to by lp
 * O(n)
 */
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL);
    assert(item != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->prev = lp->head->prev;
    new->next = lp->head;
    new->prev->next = new;
    lp->head->prev = new;
    lp->count++;
}

/**
 * remove and return the first item in the list pointed to by lp ; the list must not be empty
 * O(1)
 */
void *removeFirst(LIST *lp)
{
    assert(lp != NULL);
    NODE *remove = lp->head->next;
    void *value = remove->data;
    remove->prev->next = remove->next;
    remove->next->prev = remove->prev;
    free(remove);
    lp->count--;
    return value;
}

/**
 * remove and return the last item in the list pointed to by lp ; the list must not be empty
 * O(1)
 */
void *removeLast(LIST *lp)
{
    assert(lp != NULL);
    NODE *remove = lp->head->prev;
    void *value = remove->data;
    remove->prev->next = remove->next;
    remove->next->prev = remove->prev;
    free(remove);
    lp->count--;
    return value;
}

/**
 * return, but do not remove, the first item in the list pointed to by lp
 * the list must not be empty
 * O(1)
 */
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    return lp->head->next->data;
}

/**
 * return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
 * O(1)
 */
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    return lp->head->prev->data;
}

/**
 * if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
 * O(n)
 */
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    assert(item != NULL);
    NODE * curr = lp->head->next;

    while (curr != lp->head)
    {
        // remove
        if (lp->compare(curr->data, item) == 0)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            free(curr);
            lp->count--;
            return;
        }
        curr = curr->next;
    }
}

/**
 * if item is present in the list pointed to by lp then return the matching item, otherwise return NULL;
 * the comparison function must not be NULL
 * O(n)
 */
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    assert(item != NULL);
    NODE *curr = lp->head->next;
    int i;

    for (i = 0; i < lp->count; i++)
    {
        // remove
        if (lp->compare(curr->data, item) == 0)
        {
            return curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

/**
 * allocate and return an array of items in the list pointed to by lp
 * O(n)
 */
void *getItems(LIST *lp)
{
    assert(lp != NULL);
    void **arr = malloc(sizeof(void *) * lp->count);
    NODE *curr = lp->head->next;
    int i;
    for (i = 0; i < lp->count; i++)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
    return arr;
}

