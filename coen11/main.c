/**

Example output.txt:

 

work 1 10:01 0.00

sleep 1 23:24 23:59

drink 2 03:00 50.00

lunch 2 12:01 house

walk 3 07:30 1.00

run 3 12:30 park

 
*/

 

 

// lab 9

// winter 2023

// name: Benjamin Banh

 

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdio_ext.h>

#include "list.h" 

#include <unistd.h>

#include <pthread.h>

 

//Global Variables

struct myStruct* head[2];

pthread_mutex_t lock;
 

int main(int argc, char *argv[]){

    int option;

    printf("%s","Options:\n 1: insert\n 2: list\n");

    printf(" 3: listByHour\n 4: delete\n");

    printf(" 5: Print Backwards\n");

    printf(" 6: Show autosave file contents");

    printf(" 0: Exit and Save\n");

   

    //copied from instructions of lab8

    if (argc != 3){

        printf ("The name of the file is missing!\n");

        return 1;                                               //comment out when testing

    }

    read_file (argv[1]);
    pthread_t autosaver_thread;
    if(argc == 3){

        pthread_create(&autosaver_thread, NULL, autosaver,(void*)argv[2]);

    }

    else{

        pthread_create(&autosaver_thread, NULL, autosaver,"autosave.bin");

    }

    //pthread_mutex_init(lock, NULL);

   

    while (1){

        printf("\n");

        printf("Enter option\n  ");

        if (scanf("%d", &option) != 1){

            printf("error\n");

            return 0;

        }

        switch (option){

            case 1:

                insert(NULL);

                break;

            case 2:

                list();

                break;

            case 3:

                list_hour();

                break;

            case 4:

                delete();

                break;

            case 5:

                printf("Backwards:");

                printf("    List 1:\n");

                printReverse(head[1]);

                printf("    List 2:\n");

                printReverse(head[2]);

                printf("    List 3:\n");

                printReverse(head[3]);

                break;

            case 6:

                list_binary_file(argv[2]);

                break;

            case 0:                     //save all data to text file, deletes all nodes and quits

                pthread_mutex_lock(&lock);

                pthread_cancel(autosaver_thread);

                pthread_mutex_unlock(&lock);

                save_to_file(argv[1]);

                                     delete_all_nodes(head[1]);

                                     delete_all_nodes(head[2]);

                                     delete_all_nodes(head[3]);

                                     printf("exit\n");

                return 0;

            default:

                printf("wrong option\n");

        }

    }

}

 

// void insert (struct node);

/**

* Read the new task information to a local struct

before calling the insert function

–You may use an extra function for that

*/

void insert(struct myStruct* node){

    pthread_mutex_lock(&lock);

    struct myStruct* newNode = NULL;

   

    if(!node){

        user_Insert();

        pthread_mutex_unlock(&lock);

        return;

    }

    //add node from savefiles

    else{

        newNode = node;

        newNode->next = NULL;

       

        if (head[newNode->priority]==NULL){   //list is empty

            head[newNode->priority]=newNode;

            pthread_mutex_unlock(&lock);

            return;

        }

        struct myStruct *ptr = head[newNode->priority];

       

        //appends node to end of the linked list

        while (ptr->next != NULL)

            ptr = ptr->next;

 

        ptr->next = newNode;

        pthread_mutex_unlock(&lock);

    }

}

 

 

void user_Insert(void){

    struct myStruct* newNode = (struct myStruct*)malloc(sizeof(struct myStruct));

    printf("Enter task:\n");

    printf("    ");

    __fpurge(stdin);

    scanf("%[^'\n']", newNode->tasks);

   

    printf("Enter Priority(1,2,3):\n");

    printf("    ");

    scanf("%d", &newNode->priority);

   

    printf("Enter time(hour):\n");

    printf("    ");

    scanf("%d", &newNode->hours);

   

    printf("Enter time(minute):\n");

    printf("    ");

    scanf("%d", &newNode->minutes);

   

    if (newNode->hours < 0 || newNode->hours > 24 || newNode->minutes < 0 || newNode->minutes > 60)

    {

        printf("Not valid time\n");

        return;

    }

   

    if (newNode->priority <= 0 || newNode->priority > 3){

        printf("That is not a valid priority\n\n");

        return;

    }

   

    if (check_duplicate(newNode->tasks) == 1){

        printf("That is a repeat task\n\n");

        return;

    }

   

    //for union info

    if (newNode->hours < 12){

        printf("Enter budget(float):\n");

        printf("    ");

        scanf("%f", &newNode->info.budget);

    }

    else if(newNode->hours < 20){

        printf("Enter location(string):\n");

        printf("    ");

        scanf("%s", newNode->info.location);

    }

    else if(newNode->hours < 24){

        printf("Enter endtime(hour):\n");

        printf("    ");

        scanf("%d", &newNode->info.endtime[0]);

       

        printf("Enter endtime(minutes):\n");

        printf("    ");

        scanf("%d", &newNode->info.endtime[1]);

        if (newNode->info.endtime[0] <= 0 || newNode->info.endtime[0] > 24 || newNode->info.endtime[1] <= 0 || newNode->info.endtime[1] > 60){

            printf("Not valid time\n");

            return;

        }

    }

    else{

        printf("Not valid time\n");

        return;

    }

    newNode->next = NULL;

   

    //sort the linked list based on time

    if (head[newNode->priority]==NULL){   //list is empty

        head[newNode->priority]=newNode;

        return;

    }

   

    struct myStruct *prev=NULL;

    struct myStruct* current = head[newNode->priority];

   

    while (current != NULL && (newNode->hours > current->hours ||

            (newNode->hours == current->hours && newNode->minutes > current->minutes))){

        prev=current;

        current=current->next;

    }

    if (prev==NULL){

        newNode->next=head[newNode->priority];

        head[newNode->priority]=newNode;

    }

    else{

        prev->next=newNode;

        newNode->next=current;

    }

}

 


 

//deletes task, hour, minutes given task name

void delete(){

    //pthread_mutex_lock(&lock);

    char dTask[20];

    int i;

    struct myStruct* temp;

    struct myStruct* prev;

   

    printf("Enter task to delete:\n");

    printf("    ");

    __fpurge(stdin);

    scanf("%[^'\n']", dTask);

   

    for(i = 1; i < 4; i++){
	
        temp = head[i];

	//if head has name delete

        if (temp != NULL && strcmp(temp->tasks, dTask) == 0){

            head[i] = temp->next;

            free(temp);

            printf("%s deleted from the %d task list\n\n", dTask, i);

            return;

        }

       

        while(temp != NULL && strcmp(temp->tasks, dTask) != 0){

            prev = temp;

            temp = temp->next;

        }

        if (temp == NULL){
	    if(i != 3)continue;
    	    printf("Task not found\n");
	    printf("%d",i);

            return;

        }

        prev->next = temp->next;

        printf("%s deleted from the %d task list\n\n", dTask, i);

        free(temp);
	return;
    }

    //pthread_mutex_unlock(&lock);

}

 

//used in insert function

int check_duplicate(char str[]){

    struct myStruct *ptr;

    int i;

    for(i = 1; i < 4; i++){

        ptr = head[i];

        while(ptr != NULL){

            if(strcmp(str,ptr->tasks) == 0)

                return 1;

            ptr = ptr->next;

        }

    }

    return 0;

}


//node is head[i]

void printReverse(struct myStruct* node)

{

    // Base case

    if (node == NULL)

       return;

    // print the list after head node

    printReverse(node->next);

    // After everything else is printed, print head

    printf("        %02d:", node -> hours);

    printf("%02d ", node -> minutes);

    printf("%s ", node -> tasks);

   

    //union

    if (node -> hours >= 0 && node -> hours < 12)

        printf(" Budget: %.2f", node -> info.budget);

    else if(node -> hours < 20)

        printf(" Location: %s", node -> info.location);

    else if(node -> hours < 24)

        printf(" Endtime: %d:%02d", node -> info.endtime[0],node -> info.endtime[1]);

    printf("\n");

}
	
