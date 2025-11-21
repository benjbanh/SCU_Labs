#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdio_ext.h>

#include "list.h"

#include <unistd.h>

#include <pthread.h>


void list(void){

    pthread_mutex_lock(&lock);

    int i;

    for(i = 1; i < 4; i++){

        struct myStruct *ptr;

        ptr = head[i];

       

        printf("    List %d:\n", i);

        if(ptr == NULL){

            printf("        No tasks in List\n");

            continue;

        }

        while(ptr != NULL){

            printf("        %02d:", ptr -> hours);

            printf("%02d ", ptr -> minutes);

            printf("%s ", ptr -> tasks);

           

            //union

            if (ptr -> hours >= 0 && ptr -> hours < 12)

                printf(" Budget: %.2f", ptr -> info.budget);

            else if(ptr -> hours < 20)

                printf(" Location: %s", ptr -> info.location);

            else if(ptr -> hours < 24)

                printf(" Endtime: %d:%02d", ptr -> info.endtime[0],ptr -> info.endtime[1]);

            printf("\n");

            ptr = ptr->next;

        }

    }

    pthread_mutex_unlock(&lock);

}

 

void list_hour(void){

    pthread_mutex_lock(&lock);

    int hour;

    int i;

   

    printf("%s", "Enter Hour:\n");

    printf("%s", " ");

    scanf("%d", &hour);

   

    for(i = 1; i < 4; i++){

        struct myStruct *ptr;

        ptr = head[i];

   

        printf("%d List:\n", i);

        while(ptr != NULL){

            if (ptr -> hours == hour){

                printf("    %02d:", ptr -> hours);

                printf("%02d ", ptr -> minutes);

                printf("%s ", ptr -> tasks);

               

                //union

                if (ptr -> hours >= 0 && ptr -> hours < 12)

                    printf(" Budget: %.2f", ptr -> info.budget);

                else if(ptr -> hours < 20)

                    printf(" Location: %s", ptr -> info.location);

                else if(ptr -> hours < 24)

                    printf(" Endtime: %d:%02d", ptr -> info.endtime[0], ptr -> info.endtime[1]);

                printf("\n");

            }

            ptr = ptr->next;

        }

    }

    pthread_mutex_lock(&lock);

}

