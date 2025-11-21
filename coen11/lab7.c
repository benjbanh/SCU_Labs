//
// lab 7
// winter 2023
// name: Benjamin Banh

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

//Function Prototypes
int main(void);
void insert();                              //option 1
void list();                                //option 2
void list_hour();                           //option 3
void delete();                              //option 4
int check_duplicate(char arr[]);
void save_to_file();
void read_file();                           //new
void delete_all_nodes();


//structure and union
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
    struct myStruct* next;
};

//Global Variables
struct myStruct* head = NULL;


int main(void){
    int option;
    printf("%s","Options:\n 1: insert\n 2: list\n");
    printf(" 3: listByHour\n 4: delete\n");
    printf(" 5: deletebyHour\n");
    printf(" 0: Exit and Save\n");
    
    while (1){
        printf("\n");
        printf("Enter option\n");
        if (scanf("%d", &option) != 1){
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

//Same as lab 7, but add the priority and insert in the priolist (index=prio-1)
//Function check_duplicate needs to traverse the 3 lists
void insert(void){
    struct myStruct* newStruct = (struct myStruct*)malloc(sizeof(struct myStruct));
    
    printf("Enter task:\n");
    printf("    ");
    __fpurge(stdin);
    scanf("%[^'\n']", newStruct->tasks);

    printf("Enter time(hour):\n");
    printf("    ");
    scanf("%d", &newStruct->hours);
    
    printf("Enter time(minute):\n");
    printf("    ");
    scanf("%d", &newStruct->minutes);

    if (newStruct->hours < 0 || newStruct->hours > 24 || newStruct->minutes < 0 || newStruct->minutes > 60)
    {
        printf("Not valid time\n");
        return;
    }
    
    if (check_duplicate(newStruct->tasks) == 1){
        printf("That is a repeat task\n\n");
        return;
    }
    
    //for union info
    if (newStruct->hours < 12 && newStruct->hours >= 0){
        printf("Enter budget(float):\n");
        printf("    ");
        scanf("%f", &newStruct->info.budget);
    }
    else if(newStruct->hours < 20){
        printf("Enter location(string):\n");
        printf("    ");
        scanf("%s", newStruct->info.location);
    }
    else if(newStruct->hours < 24){
        printf("Enter endtime(hour):\n");
        printf("    ");
        scanf("%d", &newStruct->info.endtime[0]);
        
        printf("Enter endtime(minutes):\n");
        printf("    ");
        scanf("%d", &newStruct->info.endtime[1]);
        if (newStruct->info.endtime[0] <= 0 || newStruct->info.endtime[0] > 24 || newStruct->info.endtime[1] <= 0 || newStruct->info.endtime[1] > 60){
            printf("Not valid time\n");
            return;
        }
    }
    else{
        printf("Not valid time\n");
        return;
    }
    newStruct->next = NULL;
    
    //sort the linked list based on time
        if (head==NULL)//list is empty
        {
            head=newStruct;
            return;
        }
        struct myStruct *prev=NULL;
        struct myStruct* current = head;
        
        while (current != NULL && (newStruct->hours > current->hours || (newStruct->hours == current->hours && newStruct->minutes > current->minutes)))
        {
                prev=current;
                current=current->next;
        }
        if (prev==NULL)
        {
                newStruct->next=head;
                head=newStruct;
        }
        else
        {
                prev->next=newStruct;
                newStruct->next=current;
        }
}

void list(void){
    struct myStruct *ptr;
    ptr = head;
    
    printf("List of Tasks:\n");
    if(ptr == NULL){
        printf("    No tasks in List\n");
        return;
    }
    else{
	while(ptr != NULL){
        	printf("    %02d:", ptr -> hours);
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
    struct myStruct *ptr;
    ptr = head;
    
    printf("%s", "Enter Hour:\n");
    printf("%s", " ");
    scanf("%d", &hour);

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
                printf(" Endtime: %d:%02d", ptr -> info.endtime[0],ptr -> info.endtime[1]);
            printf("\n");
        }
        ptr = ptr->next;
    }
}

//deletes task, hour, minutes given task name
void delete(){
    char dTask[20];
    struct myStruct* temp = head;
    struct myStruct* prev;
    
    printf("Enter task to delete:\n");
    printf("    ");
    __fpurge(stdin);
    scanf("%[^'\n']", dTask);
    
    //if head has name delete
    if (temp != NULL && strcmp(temp->tasks, dTask) == 0){
        head = temp->next;
        free(temp);
        printf("%s deleted from the task list\n\n", dTask);
        return;
    }
    
    while(temp != NULL && strcmp(temp->tasks, dTask) != 0){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Task not found\n");
        return;
    }
    prev->next = temp->next;
    printf("%s deleted from the task list\n\n", dTask);
    free(temp);
}

//used in insert function
int check_duplicate(char str[]){
    struct myStruct *ptr = head;
    
    while(ptr != NULL){
        if(strcmp(str,ptr->tasks) == 0)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

void save_to_file(){
    FILE *outfile;
    struct myStruct *ptr;
    ptr = head;
    outfile = fopen("output.txt", "w");
    while(ptr != NULL){
        fprintf(outfile, "%s %02d:%02d ", ptr->tasks, ptr->hours, ptr->minutes);
        
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
    fclose(outfile);
}

void delete_all_nodes(){
    struct myStruct *current = head;
    struct myStruct *next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

