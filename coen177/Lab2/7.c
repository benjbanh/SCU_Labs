/* Name: Benjamin Banh
 * Date: 10/1/2
 * Title: Lab 2: Programming in C and Use of System Calls
 * Description:  Rewrite the program in Step 1, so that the child process runs the ls command only and the parent
            process just waits until the child process terminates before exiting.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <sys/wait.h> /* wait */

/* main function */
int main() {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if(pid == 0){
        execlp("/bin/ls", "ls", 0);
    }
    else {
        wait(0);
        printf("Child has completed the task! \n");
        exit(0);
    }
    return 0;
}