//
// lab 4
// winter 2023
// name: Benjamin Banh

/**
 *
 * 
  – Use an union to add info to each task
    • Before noon -> float budget
    • From 12 to 20h -> char location[LENGTH]
    • After 20h ->int endtime[2] (for hour and minutes)
**/


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

union extraInfo{
    float budget;
    char location[15];
    int endtime[2];
};
struct myStruct{
    char tasks[10];
    int hours;
    int minutes;
    union extraInfo info;
};
struct myStruct taskList[10];
int counter = 0;

int main(void){
    int option;
    
    printf("%s","Options:\n 1: insert\n 2: list\n");
    printf(" 3: listByHour\n 4: delete\n");
    printf(" 5: deletebyHour\n");
    printf(" 0: Exit\n");
    
    while (1)
    {
        printf("\n");
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

void insert(void){                          //include union
    struct myStruct s;
    int i = counter - 1;

    printf("Enter task:\n");
    printf("    ");
    __fpurge(stdin);
    scanf("%[^'\n']", s.tasks);

    printf("Enter time(hour):\n");
    printf("    ");
    scanf("%d", &s.hours);
    
    printf("Enter time(minute):\n");
    printf("    ");
    scanf("%d", &s.minutes);

    if (s.hours <= 0 || s.hours > 24 || s.minutes <= 0 || s.minutes > 60)
    {
        printf("Not valid time\n");
        return;
    }
    
    if (check_duplicate(s.tasks) == 1){
        printf("That is a repeat task\n\n");
        return;
    }
    
    //for union info
    if (s.hours < 12 && s.hours >= 0){
        printf("Enter budget(float):\n");
        printf("    ");
        scanf("%f", &s.info.budget);
    }
    else if(s.hours < 20){
        printf("Enter location(string):\n");
        printf("    ");
        scanf("%s", s.info.location);
    }
    else if(s.hours < 24){
        printf("Enter endtime(hour):\n");
        printf("    ");
        scanf("%d", &s.info.endtime[0]);
        
        printf("Enter endtime(minutes):\n");
        printf("    ");
        scanf("%d", &s.info.endtime[1]);
        if (s.info.endtime[0] <= 0 || s.info.endtime[0] > 24 || s.info.endtime[1] <= 0 || s.info.endtime[1] > 60){
            printf("Not valid time\n");
            return;
        }
    }
    else{
        printf("Not valid time\n");
        return;
    }
    
    //sort here
    while(i >= 0 && (taskList[i].hours > s.hours) || (taskList[i].hours == s.hours && taskList[i].minutes > s.minutes)){
            taskList[i+1] = s;
            i--;
    }
    taskList[i+1] = s;

    counter++;
}

void list(void){                            //include union
    int i;
    struct myStruct *ptr;
    ptr = &taskList[0];
    
    printf("List of Tasks:\n");
    if(counter == 0){
        printf("    No tasks in List\n");
    }
    for (i = 0; i < counter; i++, ptr++)
    {
        printf(" %02d:", ptr -> hours);
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
    }
}

void list_hour(void){                       //include union
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
            if (ptr -> hours < 12)
                printf(" Budget: %.2f", ptr -> info.budget);
            else if(ptr -> hours < 20)
                printf(" Location: %s", ptr -> info.location);
            else
                printf(" Endtime: %d:%02d", ptr -> info.endtime[0], ptr -> info.endtime[1]);
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
               taskList[j].info = taskList[j+1].info;
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
               taskList[j].info = taskList[j+1].info;
               j++;
           }
           counter--;
        }
    }
}
