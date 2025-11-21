#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "set.h"
#include <assert.h>
#include <stdbool.h>

#define AVG_CHAIN_LENGTH 20

typedef struct set
{
    int count;
    int length;
    LIST **lists;
    int (*compare)();
    unsigned (*hash)();
} SET;

/**
 * Creates a hashtable with chaining to have sets at each index of the table
 * O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(compare != NULL && hash != NULL);
    assert(sp != NULL);
    // initialize length, count, compare, and hash
    sp->length = maxElts / AVG_CHAIN_LENGTH;
    sp->lists = malloc(sizeof(LIST *) * sp->length);
    sp->compare = compare;
    sp->hash = hash;
    sp->count = 0;
    // initialize array of lists: allocating memory for it
    for (i = 0; i < sp->length; i++)
    {
        sp->lists[i] = createList(compare);
    }
    // for each element in the lists array(sp->lists[i]), create list, and let sp->lists[i] point to it.
    return sp;
}

/**
 * Frees the given set
 * O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->length; i++)
    {
        destroyList(sp->lists[i]);
    }
    free(sp->lists);
    free(sp);
}

/**
 * Returns the number of elements
 * O(1)
 */
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

/**
 * Adds an element elt to the given set sp
 * O(1)
 */
void addElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    int hash = ((*sp->hash)(elt)) % (sp->length);
    addLast(sp->lists[hash], elt);
    sp->count++;
}

/**
 * Removes the given element from the set
 * O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    int hash = ((*sp->hash)(elt)) % (sp->length);
    if (findItem(sp->lists[hash], elt) != NULL)
    {
        removeItem(sp->lists[hash], elt);
        sp->count--;
    }
}

/**
 * Finds the given element in the hashtable sp
 * O(n)
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    int hash = ((*sp->hash)(elt)) % (sp->length);
    return findItem(sp->lists[hash], elt);
}

/**
 * Returns the all elements in the hashtable by returning an array
 * O(n)
 */
void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **items = malloc(sizeof(void *) * sp->count);
    int i, j;
    for (i = 0, j = 0; i < sp->length; i++)
    {
        void **elements = getItems(sp->lists[i]);
        memcpy(items + j, elements, sizeof(void *) * numItems(sp->lists[i]));
        j += numItems(sp->lists[i]);
        free(elements);
    }
    return items;
}

