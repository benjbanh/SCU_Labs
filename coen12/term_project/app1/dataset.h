#ifndef DATASET_H_
#define DATASET_H_

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef struct node NODE;
typedef struct set SET;
typedef struct list LIST;

SET *createDataSet(int max);
void destroyDataSet(SET *sp);
int searchAge(SET *sp, int age);
void insert(SET *sp, int id, int age);
void delete(SET *sp, int id);
int maxAgeGap(SET *sp);

#endif
