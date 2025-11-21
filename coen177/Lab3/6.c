// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 6

// # Desription: Step 6. [15%] Write a C program that implements some form of producer-consumer message communication
// using a shared memory segment

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

char msg1[60];

// main
int main(int argc,char *argv[]){
    int fds[2];
    char buff[60];
    
    key_t key;
    int shmid;
    char *ctrl;
    
    // Generate a unique key for shared memory
    key = ftok("shmfile", 65);

    shmid = shmget(key, 1024, IPC_CREAT | 0666);

    pid_t pid = fork();

    if (pid==0){ //child consumer
        sleep(1);
        ctrl = (char*) shmat( shmid, 0, 0);
        printf("Message: \"%s\"\n", ctrl);
        shmdt(ctrl);

    }
    else{ //parent producer
        sleep(1);
        ctrl = (char*) shmat( shmid, 0, 0);
        char message[] = "Hello World!";
        strcpy(ctrl, message);
        shmdt(ctrl);

        wait(0);
        shmctl(shmid, IPC_RMID, NULL);

    }
    
    return 0;
}

