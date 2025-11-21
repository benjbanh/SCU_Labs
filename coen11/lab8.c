/**
Example output.txt:

work 1 10:01 0.00
sleep 1 23:24 23:59
drink 2 03:00 50.00
lunch 2 12:01 house
walk 3 07:30 1.00
run 3 12:30 park

*/


// lab 8
// winter 2023
// name: Benjamin Banh

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

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
void read_file(char fName[]);                           //new
void delete_all_nodes();

//Global Variables
struct myStruct* head[2];


int main(int argc, char *argv[]){
    int option;
    printf("%s","Options:\n 1: insert\n 2: list\n");
    printf(" 3: listByHour\n 4: delete\n");
    printf(" 5: deletebyHour\n");
    printf(" 0: Exit and Save\n");
    
    //copied from instructions of lab8
    if (argc == 1){
        printf ("The name of the file is missing!\n");
        return 1;
    }
    read_file (argv[1]);
    
    while (1){
        printf("\n");
        printf("Enter option\n");
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
            case 0:                     //save all data to text file, deletes all nodes and quits
                save_to_file();
			    delete_all_nodes();
			printf("exit\n");
                return 0;
            default:
                printf("wrong option\n");
        }
    }
}

void insert(struct myStruct* node){
    struct myStruct* newNode = NULL;
    
    if(!node){
        user_Insert();
        return;
    }
    //add node from savefiles
    else{
        newNode = node;
        newNode->next = NULL;
        
        if (head[newNode->priority]==NULL){   //list is empty
            head[newNode->priority]=newNode;
            return;
        }
        struct myStruct *ptr = head[newNode->priority];
        
        //appends node to end of the linked list
        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = newNode;
        return;    
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

void list(void){
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
}

void list_hour(void){
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
}

//deletes task, hour, minutes given task name
void delete(){
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
            if(i != 3)
	      continue;
	    printf("Task not found\n");
            return;
        }
        prev->next = temp->next;
        printf("%s deleted from the %d task list\n\n", dTask, i);
        free(temp);
    }
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

//Receive file name as an argument
void save_to_file(char s[]){
    FILE *outfile;
    int i;
    struct myStruct *ptr;
    outfile = fopen("output.txt", "w");
    
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
}

void delete_all_nodes(){
    int i;
    for(i = 1; i < 4; i++){
        struct myStruct *current = head[i];
        struct myStruct *next;
        while(current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        head[i] = NULL;
    }
}

// Call insert to insert the data read from file
void read_file(char fName[]){
    FILE* ptr;
    char str[255];
    char* token;

    ptr = fopen(fName,"r");
    
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
        temp-
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

