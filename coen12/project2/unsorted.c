#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"

typedef struct set {
    int count; //number of strings
    int length; //length of the array
    char **data; // pointer to an array for strings
} SET;

//O(n)
static int search(SET *set, char *elt){
    assert(set != NULL);
    
    int i;
    for(i=0; i < set->count; i++){
        if(strcmp(set->data[i],elt) == 0 ){
            return i;
        }
    }
    return -1;
    
}
//O(1)
SET *createSet(int maxElts){
    SET *nSet;
    
    nSet = malloc(sizeof(SET));
    assert(nSet != NULL);
    nSet->data = malloc(sizeof(char *)*maxElts);
    assert(nSet->data != NULL);
    nSet->count = 0;
    nSet->length = maxElts;
    return nSet;
}

//O(N)
void destroySet(SET *sp){
    int i;
    
    assert(sp != NULL);
    for(i = 0; i < sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

//O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp->count;
}

//O(N)
void addElement(SET *sp, char *elt){
    //check for duplicates
    if(search(sp,elt) != -1) return;
    if(sp->count > sp-> length) return;
    //add to SET
    sp->data[sp->count] = strdup(elt);
    (sp->count)++;
}

//O(N)
void removeElement(SET *sp, char *elt){
    int index = search(sp,elt);
    //find elt
    if(index == -1) return;
    //remove index
    free(sp->data[index]);
    sp->data[index] = sp->data[sp->count-1];
    sp->count--;
}

//O(N)
char *findElement(SET *sp, char *elt){
    int index = search(sp,elt);
    if(index == -1) return NULL;
    return sp->data[index];
}

//O(N)
char **getElements(SET *sp){
    assert(sp != NULL);
    char** temp = malloc(sizeof(char*)*sp-> count);
    int i;
    for(i = 0; i < sp->count; i++ )
        temp[i] = sp->data[i];
    return temp;
}

