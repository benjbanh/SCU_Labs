/**
 * @author Benjamin Banh
 */

// Preprocessors
#include "dataset.h"

// Defines array states for hashtable
#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set
{
    int *age;
    int *flags;
    int *id;
    int count;
    int length;
};

/**
 * Creates a hashtable with a given size
 *
 * @param max the size of the set being created
 * @return the created SET
 */
SET *createDataSet(int max)
{
    // creates set
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    // initialize struct elements
    sp->age = malloc(sizeof(int) * max);
    sp->id = malloc(sizeof(int) * max);
    sp->flags = malloc(sizeof(int) * max);
    sp->count = 0;
    sp->length = max;

    // initializes the flags array to be empty
    int i;
    for (i = 0; i < max; i++)
    {
        sp->flags[i] = EMPTY;
    }
    printf("Created\n");
    return sp;
}

/**
 * Destroys and frees given data set
 *
 * @param sp a pointer to the set whose data will be freed
 */
void destroyDataSet(SET *sp)
{
    assert(sp != NULL);
    free(sp);
    printf("Destroyed Set\n");
}

/**
 * Searches the given set and returns whether or not that id is in the set
 *
 * @param sp the set searched
 * @param id the id searched
 * @return the id if found in the set, otherwise -1
 */
int searchID(SET *sp, int id)
{
    assert(sp != NULL);
    int i;

    // checks whether or not that id is in the set
    if (sp->flags[id] == FILLED && sp->id == &id)
    {
        return id;
    }
    return -1;
}

/**
 * Inserts student into the set by age parameter
 *
 * @param sp the set searched
 * @param id the id of the student inserted
 * @param age the age of the student inserted
 */
void insert(SET *sp, int id, int age)
{
    assert(sp != NULL);
    // checks whether or not the id is in the set
    int index = searchID(sp, id);
    assert(sp->count < sp->length);

    if (index != -1)
    {
        // inserts student to the set
        sp->id = &id;
        sp->age = &age;
        sp->flags[index] = FILLED;
        sp->count++;
    }
    printf("Inserted ID:%d AGE:%d\n", id, age);
}

/**
 * Deletes all students with given age from the set
 *
 * @param sp the set being searched
 * @param id the id being searched
 */
void delete(SET *sp, int id)
{
    // checks whether or not the id is in the set
    assert(sp != NULL);
    int index = searchID(sp, id);

    // marks the set's flag[index] to be deleted so identical id can replace the index
    if (index == -1)
    {
        sp->flags[index] = DELETED;
        sp->count--;
        printf("DELETED ID:%d\n", id);
    }
    else
        printf("DELETED FAILED\n");
}

