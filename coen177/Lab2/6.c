/* Name: Benjamin Banh
 * Date: 10/1/2
 * Title: Lab 2: Programming in C and Use of System Calls
 * Description:  Write a C program that becomes 5 processes (including the parent) so that each process iterates
                with a different delay taken as a command-line argument. In this case, you will have 5 command-line
                arguments. 
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <sys/wait.h> /* wait */

/* main function */
int main(int argc, char *argv[]) {
    if (argc != 6){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }

    int i;
    int id = 0;
    int n[4] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])};

    printf("\n Before forking.\n");
    pid_t pid = fork();
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    if (pid2==0 && pid1==0 && pid==0) {
        id = 1; // 1
    } 
    else if (pid2==0 && pid1==0 && pid>0) {
        id = 2; // 2
    }
    else if (pid2==0 && pid1>0 && pid==0) {
        id = 3; // 3
    }
    else if (pid2==0 && pid1>0 && pid>0) {
        id = 4; // 4
    }
    else if (pid2>0 && pid1==0 && pid==0) {
        id = 5; // 5
    }
    else if (pid2>0 && pid1==0 && pid>0) {
        exit(0);
    }
    else if (pid2>0 && pid1>0 && pid==0) {
        exit(0);
    }
    else {
        exit(0);
    }
    
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
    // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(n[id]);
        }
        wait(NULL);
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n[id]);
        }
    }
    return 0;
}