#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdio_ext.h>

#include "list.h"

#include <unistd.h>

#include <pthread.h>

void* autosaver(void* arg) {

    int i;

    FILE *bfp;

    while (1) {

        if((bfp = fopen((char *) arg, "wb")) == NULL){

             printf("Error loading autosave file.\n");

        }

        else{

            pthread_mutex_lock(&lock);

            for(i = 1; i < 4; i++){

                struct myStruct* current = head[i];

                while (current != NULL) {

                    fwrite(current, sizeof(struct myStruct), 1,bfp);

                    current = current -> next;

                }

            }

            pthread_mutex_unlock(&lock);

                      }

        fclose(bfp);

        sleep(5); // Wait for 5 seconds before saving again

    }

}

 

void list_binary_file(char* fName){

    struct myStruct ptr;

           FILE *fp;

           pthread_mutex_lock(&lock);

	   if((fp = fopen(fName,"rb")) == NULL){

                      printf("Error opening file.\n");

                      return;

           }

           while(fread(&ptr,sizeof(struct myStruct),1,fp) == 1){

                      printf("        %02d:", ptr.hours);

        printf("%02d ", ptr.minutes);

        printf("%d ", ptr.priority);

        printf("%s ", ptr.tasks);

       

        //union

        if (ptr.hours >= 0 && ptr.hours < 12)

            printf(" Budget: %.2f", ptr.info.budget);

        else if(ptr.hours < 20)

            printf(" Location: %s", ptr.info.location);

        else if(ptr.hours < 24)

            printf(" Endtime: %d:%02d", ptr.info.endtime[0],ptr.info.endtime[1]);

        printf("\n");

           }

        pthread_mutex_unlock(&lock);

}

 

//Receive file name as an argument

void save_to_file(char* fName){

    pthread_mutex_lock(&lock);

    FILE *outfile;

    int i;

    struct myStruct *ptr;

    outfile = fopen(fName, "w");

   

    for(i = 1; i < 4; i++){

        ptr = head[i];

        while(ptr != NULL){

            fprintf(outfile, "%s %d %02d:%02d ", ptr->tasks, ptr->priority, ptr->hours, ptr->minutes);

           

            if (ptr -> hours >= 0 && ptr -> hours < 12){

                fprintf(outfile, "%.2f\n", ptr -> info.budget);

            }

            else if (ptr -> hours >= 12 && ptr -> hours < 20){

                fprintf(outfile, "%s\n", ptr -> info.location);

            }

            else{

                fprintf(outfile, "%02d:%02d\n", ptr -> info.endtime[0], ptr -> info.endtime[1]);

            }

            ptr = ptr -> next;

        }

    }  

    fclose(outfile);

    pthread_mutex_unlock(&lock);

}

 

void delete_all_nodes(struct myStruct* node){   //delete binary file as well

    if (node == NULL)

        return;

    delete_all_nodes(node->next);

    free(node);

}

 

 

 

// Call insert to insert the data read from file

void read_file(char fName[]){

    FILE* ptr;

    char str[255];

    char* token;

 

    //replace "output.txt" with fName

    ptr = fopen(fName,"r");                                 //change fName to "output.txt"

   

    //if file is empty or doesn't exist

    if (ptr == NULL) {

        printf("file can't be opened \n");

        return;

    }

    //save values in file to linked lists

    while (fgets(str,sizeof(str),ptr)){

        struct myStruct* temp = (struct myStruct*)malloc(sizeof(struct myStruct));

        //tasks

        token = strtok(str, " ");

        strcpy(temp->tasks,token);

       

        //priority

        token = strtok(NULL, " ");

        temp->priority = atoi(token);

       

        //time(hour:minute)

        token = strtok(NULL, ":");

        temp->hours = atoi(token);

        token = strtok(NULL, " ");

        temp->minutes = atoi(token);

       

        //union

        if (temp->hours < 12){

            token = strtok(NULL, " ");

            temp -> info.budget = atof(token);

        }

        else if (temp->hours < 20){

            token = strtok(NULL, "\n");

            strcpy(temp -> info.location,token);

        }

        else{

            token = strtok(NULL, ":");

            temp -> info.endtime[0] = atoi(token);

            token = strtok(NULL, " ");

            temp -> info.endtime[1] = atoi(token);

        }

        temp->next = NULL;

       

        insert(temp);

    }

    fclose(ptr);

    printf("Successfully updated");

}
