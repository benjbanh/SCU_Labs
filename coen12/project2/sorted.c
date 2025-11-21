#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

typedef struct set {
    int count; //number of strings
    int length; //length of the array
    char **data; // pointer to an array for strings
} SET;

//O(logN)
static int search(SET *sp, char *elt, bool *found){
    assert(sp != NULL);
    int high = sp->count -1;
    int low = 0;
    int mid = 0;
    *found = false;

    while(low <= high){
        mid = (high + low)/2;
        
        if((strcmp(elt,sp->data[mid]) == 0)){
            *found = true;
            return mid;
        }
        else if((strcmp(elt,sp->data[mid]) < 0)){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
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
void addElement(SET *sp, char *elt){    //shift down
    assert(sp != NULL);
    bool found = true;
    int i;
    int index = search(sp, elt, &found);

    if(found == false){
        if(sp->count < sp->length) {
            for(i = sp->count; i > index; i--){
                sp->data[i] = sp->data[i-1];
            }
            sp->data[index] = strdup(elt);
            (sp->count)++;
            return;
        }
    }
}


//O(N)
void removeElement(SET *sp, char *elt){
    assert(sp != NULL);
    bool found;
    int i;
    int index = search(sp,elt,&found);
    //find elt
    if(found == true){
        free(sp->data[index]);
		for(i=index; i<sp->count; i++){
			sp->data[i] = sp->data[i+1];
		}
		sp->count--;
    }
}

//O(logN)
char *findElement(SET *sp, char *elt){
    bool found = false;
    int index = search(sp,elt,&found);
    if(found == false) return NULL;
    return sp->data[index];
}

//O(N)
char **getElements(SET *sp){
    int i;
    assert(sp != NULL);
    char **temp = malloc(sizeof(char *)*sp->count);
    for(i=0; i<sp->count; i++)
		temp[i] = sp->data[i];
    return temp;
}


