#ifndef DATASET_H
#define DATASET_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef struct set SET;

SET *createDataSet(int max);
void destroyDataSet(SET *sp);
int searchID(SET *sp, int id);
void insert(SET *sp, int id, int age);
void delete(SET *sp, int id);

#endif
