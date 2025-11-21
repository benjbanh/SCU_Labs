#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

int main(void);
void insert();                              //option 1
void list();                                //option 2
void list_hour();                           //option 3
void delete();                              //option 4
int check_duplicate(char arr[]);            
void deletebyhour();                        //option 5

struct myStruct{
    char tasks[10];
    int hours;
    int minutes;
};

struct myStruct taskList[10];
int counter = 0;

int main(void){
    int option;
    
    printf("%s","Options:\n 1: insert\n 2: list\n");
    printf(" 3: listByHour\n 4: delete\n");
    printf(" 5: deletebyHour\n");
    printf(" 0:Exit\n");
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
            case 5:
                deletebyhour();
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
    while(i >= 0 && (taskList[i].hours > nHour) || (taskList[i].hours == nHour && taskList[i].minutes > nMinute)){
            strcpy(taskList[i].tasks,taskList[i].tasks);
            taskList[i+1].hours = taskList[i].hours;
            taskList[i+1].minutes = taskList[i].minutes;
            i = i - 1;
    }
    strcpy(taskList[i+1].tasks, nTask);
    taskList[i+1].hours = nHour;
    taskList[i+1].minutes = nMinute;

    counter++;
}

void list(void){
    int i;
    struct myStruct *ptr;
    ptr = &taskList[0];
    
    printf("List of Tasks:\n");
    if(counter == 0){
        printf("    No tasks in List\n");
    }
    for (i = 0; i < counter; i++, ptr++)
    {
        printf(" ");
        printf("%02d", ptr -> hours);
        printf(":");
        printf("%02d", ptr -> minutes);
        printf(" ");
        printf("%s", ptr -> tasks);
        printf("\n");
    }
}

void list_hour(void){
    int hour;
    int i;
    struct myStruct *ptr;
    ptr = &taskList[0];
    
    printf("%s", "Enter Hour:\n");
    printf("%s", " ");
    scanf("%d", &hour);

    for (i = 0; i < counter; i++)
    {
        if (ptr -> hours == hour)
        {
            printf("%s", "  Task:");
            printf("%s", ptr -> tasks);
            printf("\n");
        }
        ptr++;
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
        if(strcmp(dTask, taskList[i].tasks) == 0){
            j=i;
           //delete by shift over
           while(j + 1 <= counter){
               strcpy(taskList[j].tasks,taskList[j+1].tasks);
               taskList[j].hours = taskList[j+1].hours;
               taskList[j].minutes = taskList[j+1].minutes;
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
        if(strcmp(str,taskList[i].tasks) == 0)
            return 1;
    }
    return 0;
}

//deletes all tasks at the specified hour
void deletebyhour(){
    int i,j;
    int dHour;
    
    //needs to have scanner which asks task name
    printf("Enter hour tasks with should be deleted:\n");
    printf("    ");
    scanf("%d", &dHour);
    
    //loop to delete task
    for(i = 0; i < counter; i++){
        if(taskList[i].hours > dHour )
            break;
        while(dHour == taskList[i].hours){
            j=i;
           //delete by shift over
           while(j + 1 <= counter){
               strcpy(taskList[j].tasks,taskList[j+1].tasks);
               taskList[j].hours = taskList[j+1].hours;
               taskList[j].minutes = taskList[j+1].minutes;
               j++;
           }
           counter--;
        }
    }
}
