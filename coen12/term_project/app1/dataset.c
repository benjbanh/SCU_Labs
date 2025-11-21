/**
 * @author Benjamin Banh
 */

// Preprocessors
#include "dataset.h"

// structures
struct node
{
    int id;
    int age;
    NODE *next;
};

struct list
{
    NODE *head;
    int count;
};

struct set
{
    LIST **list;
    int count;
    int length;
};

/**
 * Creates a hashtable with 12 lists, each with a circularly linked list for every student, ordered by age
 *
 * @param max the size of the set being created
 * @return the created SET
 */
SET *createDataSet(int max)
{
    // initialize set
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = max;
    sp->list = malloc(sizeof(LIST *) * 13);

    // initialize list
    int i;
    for (i = 0; i < 13; i++)
    {
        sp->list[i] = malloc(sizeof(LIST));
        sp->list[i]->head = malloc(sizeof(NODE));
        assert(sp->list[i]->head != NULL);
        sp->list[i]->head->next = sp->list[i]->head;
        sp->list[i]->count = 0;
    }
    printf("Created Set\n");
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
    int i;
    // loops over the list for every age
    for (i = 0; i < 13; i++)
    {
        // frees all nodes in the list
        if (sp->list[i]->count > 0)
        {
            NODE *curr;
            NODE *next = sp->list[i]->head->next;
            while (curr != sp->list[i]->head)
            {
                curr = next;
                next = curr->next;
                free(curr);
            }
        }
        free(sp->list[i]);
    }
    free(sp);
    printf("Destroy Set\n");
}

/**
 * Searches the given set and returns whether or not that age is in the set
 *
 * @param sp the set searched
 * @param age the age searched
 * @return 1 if found, otherwise 0
 */
int searchAge(SET *sp, int age)
{
    assert(sp != NULL);
    if (sp->list[age - 18]->count > 0)
        return 1;
    return 0;
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
    assert(sp != NULL && sp->count < sp->length);

    // creates and assigns values to the to be inserted node
    NODE *node = malloc(sizeof(NODE));
    assert(node != NULL);
    node->id = id;
    node->age = age;

    // insert new node into the start of the linked list
    int index = age - 18;
    node->next = sp->list[index]->head->next;
    sp->list[index]->head->next = node;

    // increment count
    sp->list[index]->count++;
    sp->count++;
    printf("Inserted ID:%d Age:%d\n", id, age);
}

/**
 *  Deletes all students with given age from the set
 *
 * @param sp the set being searched
 * @param age the age being searched
 */
void delete(SET *sp, int age)
{
    assert(sp != NULL);
    printf("Beginning Delete:\n");
    // checks whether or not a student with the specified age exists within the set
    if (searchAge(sp, age) == 0)
    {
        printf("    NO STUDENTS WITH AGE %d TO DELETE\n", age);
        return;
    }

    LIST *currList = sp->list[age - 18];
    NODE *curr = currList->head->next;
    NODE *temp;
    // deletes all students with the given age from the set
    while (curr != currList->head)
    {
        temp = curr;
        curr = curr->next;
        printf("    DELETED ID:%d AGE:%d\n", temp->id, temp->age);
        free(temp);
        sp->count--;
    }
    currList->count = 0;
    currList->head->next = currList->head;
}

/**
 *  Returns the largest age gap between students in the set
 *
 * @param sp the set to be searched
 * @return the largest age gap between the students in the set
 */
int maxAgeGap(SET *sp)
{
    assert(sp != NULL);
    int low = 0;
    int high = 12;
    bool found;
    while (true)
    {
        found = false;
        // increments low if the age exists
        if (sp->list[low]->count == 0)
        {
            low++;
        }
        // decrements high if the age exists
        if (sp->list[high]->count == 0)
        {
            high--;
        }
        // if the low or high is equal or within a difference of 1(for odd count of student)
        if (found && ((high != low) || (abs(high - low) == 1)))
            continue;
        break;
    }
    int dif = high - low;
    printf("Max age gap:%d\n", dif);
    return (dif);
}

