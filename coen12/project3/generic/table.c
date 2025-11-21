#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set
{
    int count;
    int length;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
} SET;

static int search(SET *sp, void *elt, bool *found);
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, void *elt); // doesnt allocate memory
void removeElement(SET *sp, void *elt);
void *findElement(SET *sp, void *elt);
void *getElements(SET *sp);

/**
 * Searches the hashtable sp for a specified value and marks whether or not the value is found
 */
// O(n)
static int search(SET *sp, void *elt, bool *found)
{
    // printf("Search\n");
    assert(sp != NULL);

    int i;
    int avaliable = -1;
    int index;
    unsigned hash = (*sp->hash)(elt) % sp->length;
    *found = false;
    for (i = 0; i < sp->length; i++)
    {
        index = (hash + i) % sp->length;

        if (sp->flags[index] == FILLED)
        {
            if ((*sp->compare)(sp->data[index], elt) == 0)
            {
                *found = true;
                return index;
            }
        }
        else if (sp->flags[index] == EMPTY)
        {
            return avaliable == -1 ? index : avaliable;
        }
        else if (sp->flags[index] == DELETED)
        {
            if(avaliable == -1) 
            avaliable = index;
        }
    }
    *found = false;
    return avaliable;
}

/**
    Creates a hashtable given the max capacity of maxElts
*/
// O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    // printf("Create\n");
    SET *sp;
    sp = malloc(sizeof(SET));
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(void *) * maxElts);
    sp->flags = malloc(sizeof(int) * maxElts);
    assert(sp->data != NULL);
    assert(sp->flags != NULL);

    int i;
    for (i = 0; i < sp->length; i++)
    {
        sp->compare = compare;
        sp->hash = hash;
        sp->flags[i] = EMPTY;
    }
    return sp;
}

/**
 * Adds an element to the hashtable
 */
// O(n)
void addElement(SET *sp, void *elt)
{
    // printf("Add\n");
    // declare variables
    bool found;
    int index = search(sp, elt, &found);
    if (!found)
    {
        assert(sp->count < sp->length);
        sp->data[index] = elt;
        sp->flags[index] = FILLED;
        sp->count++;
    }
}

/**
 * Frees the memory associated with the given set
 */
// O(1)
void destroySet(SET *sp)
{
    // printf("Destroy\n");
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

// returns number of elements in the set
// O(1)
int numElements(SET *sp)
{
    // printf("Num\n");
    assert(sp != NULL);
    return sp->count;
}

/**
 * Removes the element elt from the given set
 */
// O(n)
void removeElement(SET *sp, void *elt)
{
    // printf("Remove\n");
    bool found;
    int index = search(sp, elt, &found);
    if (found)
    {
        sp->flags[index] = DELETED;
        sp->count--;
    }
}

/**
 * Finds whether or not the value elt is in the set sp. If it is the function will return the associated value, else
 * it will return null
 */
// O(n)
void *findElement(SET *sp, void *elt)
{
    // printf("Find\n");
    bool found = false;
    int index = search(sp, elt, &found);
    if (found == false)
        return NULL;
    return sp->data[index];
}

/**
 * Returns an copied version of the given hashtable
 */
// O(n)
void *getElements(SET *sp)
{
    // printf("Get\n");
    void **elts;
    int i, j;

    assert(sp != NULL);

    elts = malloc(sizeof(void *) * sp->count);
    assert(elts != NULL);
    for (i = 0, j = 0; i < sp->length; i++)
        if (sp->flags[i] == FILLED)
            elts[j++] = sp->data[i];
    return elts;
}
