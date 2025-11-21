#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

#define INIT_LENGTH 10
#define parent(x) (((x)-1) / 2)
#define left(x) (((x)*2) + 1)
#define right(x) (((x)*2) + 2)

struct pqueue
{
    int count;        // number of entries in array
    int length;       // length of allocated array
    void **data;      // allocated array of entried
    int (*compare)(); // comparison function
};

// O(1)
//  return a pointer to a new priority queue using compare as its comparison function
PQ *createQueue(int (*compare)())
{
    assert(compare != NULL);
    PQ *pq;
    assert(pq != NULL);
    pq = malloc(sizeof(PQ));
    pq->compare = compare;
    pq->length = INIT_LENGTH;
    pq->count = 0;
    pq->data = malloc(sizeof(void *) * pq->length);
    assert(pq->data != NULL);
    return pq;
}

// O(1)
//  deallocate memory associated with the priority queue pointed to by pq
void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

// O(1)
//  return the number of entries in the priority queue pointed to by pq
int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return pq->count;
}

// O(logn)
//  add entry to the priority queue pointed to by pq
void addEntry(PQ *pq, void *entry)
{
    // dynamically increase size of array
    if (pq->count == pq->length)
    {
        pq->length = pq->length * 2;
        pq->data = realloc(pq->data, sizeof(void *) * pq->length);
        assert(pq->data != NULL);
    }

    // add to end of heap
    pq->data[pq->count] = entry;
    pq->count++;
    int location = pq->count - 1;
    while (location >= 1)
    {
        if ((*pq->compare)(entry, pq->data[parent(location)]) < 0)
        {
            PQ *temp = pq->data[parent(location)];
            pq->data[parent(location)] = pq->data[location];
            pq->data[location] = temp;
            location = parent(location);
        }
        else
            break;
    }
}

// O(logn)
// remove and return the smallest entry from the priority queue pointed to by pq
void *removeEntry(PQ *pq) 
{
    assert(pq != NULL);
    assert(pq->count != 0);

    void *root = pq->data[0];
    pq->data[0] = pq->data[pq->count - 1];
    pq->count--;
    int index = 0;
    
    while (left(index) < pq->count)
    {
        int loc;
        if (right(index) < pq->count && pq->compare(pq->data[right(index)], pq->data[left(index)]) < 0)
            loc = right(index);
        else
            loc = left(index);

        if (pq->compare(pq->data[index], pq->data[loc]) >= 0)
        {
            PQ *temp = pq->data[loc];
            pq->data[loc] = pq->data[index];
            pq->data[index] = temp;
            index = loc;
        }
        else
            break;
    }

    return root;
}
