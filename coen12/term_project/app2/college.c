/**
 * @author Benjamin Banh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "dataset.h"

#define MAX_STUDENTS 3000

int main()
{
    int i, id, age;
    int prevID = 0;

    // sets random
    srand(time(NULL));

    // creates set
    SET *sp = createDataSet(MAX_STUDENTS);

    printf("Making students\n");
    // create 1000 random students
    for (i = 0; i < 1000; i++)
    {
        id = prevID + (rand() % (2)) + 1;
        prevID = id;
        age = (rand() % (13) + 18);
        insert(sp, id, age);
    }
    // deletes 10 random students by their ids from the set
    printf("\nDeleting Random IDs:\n");
    int j;
    for (j = 0; j < 10; j++)
    {
        int deleteIndex = (rand() % 1500) + 1;
        delete (sp, deleteIndex);
    }

    // destroys dataset
    destroyDataSet(sp);
}
