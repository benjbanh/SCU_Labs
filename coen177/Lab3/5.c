// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 5

// # Desription: Step 5. [15%] Write a C program that implements some form of producer-consumer message communication
// using pipes.
// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 2

// # Desription: Step 2. [10%] Compile and run the following program and write your observations

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char msg1[60];

// main
int main(int argc,char *argv[]){
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    
    if (fork()==0){
        close(fds[0]);
        // dup2(fds[1], 1);
        printf("Enter an input: ");
        scanf("%s", msg1);
        write(fds[1],msg1,strlen(msg1)+1);

        // close(fds[1]);
        exit(1);
    }
    else if(fork()==0){
        close(fds[1]);
        printf("Output: ");
        while((count=read(fds[0],buff,60))>0){
            printf("%s\n", buff);
        }
        // close(fds[0]);
        exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}

