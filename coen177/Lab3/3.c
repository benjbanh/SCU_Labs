// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 3

// # Desription: Step 3. [10%] Modify the program in Step 2. so that the writer process passes the output of “ls” command to the
// upstream end of the pipe instead of writing its arguments to it. You may use dup2(fds[1],1); for
// redirection and execlp("ls", "ls", 0); to run the “ls” command.

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
        execlp("ls", "ls", 0);
        exit(1);
    }
    else if(fork()==0){
        close(fds[1]);
        while((count=read(fds[0],buff,60))>0){
            printf("%s\n", buff);
        }
        close(fds[0]);
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
