/* Name: Benjamin Banh
 * Date: 10/1/2
 * Title: Lab 2: Programming in C and Use of System Calls
 * Description:  Rewrite the program in Step 1 so that the delay is determined by the user entered as a command
                line argument.
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
    if (argc != 2){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }

    pid_t pid;
    int i, n = atoi(argv[1]);
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
    // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n",getpid());
            usleep(n);
        }
        wait(NULL);
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n",getpid());
            usleep(n);
        }
    }
    return 0;
}