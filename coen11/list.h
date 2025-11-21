#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdio_ext.h> 

#include <unistd.h>

#include <pthread.h>

 

//structure and union

union extraInfo{

    float budget;

    char location[15];

    int endtime[2];

};

struct myStruct{

    char tasks[10];

    int priority;

    int hours;

    int minutes;

    union extraInfo info;

    struct myStruct* next;

};

 

 

//Function Prototypes

int main(int argc, char *argv[]);

void insert(struct myStruct* node);                              //option 1

void user_Insert();

void list();                                //option 2

void list_hour();                           //option 3

void delete();                              //option 4

int check_duplicate(char arr[]);

void save_to_file();

void read_file(char *fName);

void delete_all_nodes(struct myStruct* node);

void printReverse(struct myStruct* node);       //new

void* autosaver(void* arg);

void list_binary_file(char* fName);

 

//Global Variables

struct myStruct* head[2];
pthread_mutex_t lock;
