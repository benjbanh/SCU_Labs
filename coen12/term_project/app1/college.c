/**
 * @author Benjamin Banh
 */

// Preprocessors
#include "dataset.h"

#define MAX_STUDENTS 3000

int main()
{
    int i, id, age;
    int prevID = 0;

    //create dataset and set random
    srand(time(NULL));
    SET *sp = createDataSet(MAX_STUDENTS);

    // create 1000 random students
    for (i = 0; i < 1000; i++)
    {
        id = prevID + (rand() % (2)) + 1;
        prevID = id;
        age = (rand() % (13) + 18);
        insert(sp, id, age);
    }

    // generates and deletes a random age from the set
    printf("\nDeleting Random IDs:\n");
    int num = (rand() % (2)) + 18;
    printf("Deleting age:%d\n", num);
    delete (sp, num);

    // Finds the maximum age gap within the set
    maxAgeGap(sp);

    // destroys the set and frees the data
    destroyDataSet(sp);
}
