//
// lab 3
// winter 2023
// name: Benjamin Banh


/**
 * 
 * 6 functions
 * – main, insert, list, 
 * -    listbytime, delete, check_duplicate !!
 * 
 * 4 global variables (DONE)
 *  3 arrays: tasks, hours, minutes
 *  counter
 * 
 * Show hour and minutes as x:xx(DONE)
 *  Use %d:%02d 
 * 
 * Do not allow tasks to repeat             !!
 * 
 * List should stay in order by time(DONE)
 **/ 

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

int main(void);
void insert();
void list();

void list_hour();
void delete();    //option 4
int check_duplicate(char arr[]); //used in insert function

char tasks[10][10];
int hours[10];
int minutes[10];

int counter = 0;

int main(void){
    int option;
    while (1)
    {
        printf("Enter option\n");
        if (scanf("%d", &option) != 1)
        {
            printf("error\n");
            return 0;
        }

        switch (option){
            case 1:
                insert();
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
            case 0:
                printf("exit\n");
                return 0;
            default:
                printf("wrong option\n");
        }
    }
}

void insert(void){
    char nTask[20];
    int nHour;
    int nMinute;
    int i = counter - 1;

    printf("Enter task:\n");
    printf("    ");
    __fpurge(stdin);
    scanf("%[^'\n']", nTask);

    printf("Enter time(hour):\n");
    printf("    ");
    scanf("%d", &nHour);
    
    printf("Enter time(minute):\n");
    printf("    ");
    scanf("%d", &nMinute);

    if (nHour > 23 || nMinute > 59)
    {
        printf("Not valid time\n");
        return;
    }
    
    if (check_duplicate(nTask) == 1){
        printf("That is a repeat task\n\n");
        return;
    }
    
    //sort here
    while(i >= 0 && (hours[i] > nHour) || (hours[i] == nHour && minutes[i] > nMinute)){
            strcpy(tasks[i + 1],tasks[i]);
            hours[i + 1] = hours[i];
            minutes[i + 1] = minutes[i];
            i = i - 1;
    }
    strcpy(tasks[i + 1],nTask);
    hours[i + 1] = nHour;
    minutes[i + 1] = nMinute;

    counter++;
}

void list(void){
    int i;
    printf("List of Tasks:\n");
    for (i = 0; i < counter; i++)
    {
        printf(" ");
        printf("%d", hours[i]);
        printf(":");
        printf("%d", minutes[i]);
        printf(" ");
        printf("%s", tasks[i]);
        printf("\n");
    }
}

void list_hour(void){
    int hour;
    int i;
    printf("%s", "Enter Hour:\n");
    printf("%s", " ");
    scanf("%d", &hour);

    for (i = 0; i < counter; i++)
    {
        if (hours[i] == hour)
        {
            printf("%s", "  Task:");
            printf("%s", tasks[i]);
            printf("\n");
        }
    }
}

//deletes task, hour, minutes given task name
void delete(){
    int i,j;
    char dTask[20];
    
    //needs to have scanner which asks task name
    printf("Enter task to be deleted:\n");
    printf("    ");
    __fpurge(stdin);
    scanf("%[^'\n']", dTask);
    
    //loop to delete task
    for(i = 0; i < counter; i++){
        if(strcmp(dTask, tasks[i]) == 0){
            j=i;
           //delete by shift over
           while(j + 1 <= counter){
               strcpy(tasks[j],tasks[j+1]);
               hours[j] = hours[j+1];
               minutes[j] = minutes[j+1];
               j++;
           }
        //   tasks[counter] ='\0';
           counter--;
        }
    }
}

//used in insert function
int check_duplicate(char str[]){
    int i;
    for(i = 0; i < counter; i++){
        if(strcmp(str,tasks[i]) == 0)
            return 1;
    }
    return 0;
}
