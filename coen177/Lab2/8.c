/* Name: Benjamin Banh
 * Date: 10/1/2
 * Title: Lab 2: Programming in C and Use of System Calls
 * Description:   Step 8. [15%] Rewrite the program in Step 3 with two threads instead of two processes. When your program
compiles without errors or warnings, upload the source file to Camino.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
// #include <sys/wait.h> /* wait */

#include <pthread.h>

void* foo1(void* arg){
    int delay = *(int*)arg;
    for (int i=0;i<10;i++) {
        printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
        usleep(delay);
    }
    return NULL;
}

void* foo2(void* arg){
    int delay = *(int*)arg;
    // Child process: pid = 0
    for (int j=0;j<10;j++) {
        printf("I am the child process displaying iteration %d\n",j);
        usleep(delay);
    }
    return NULL;
}

/* main function */
int main(int argc, char *argv[]) {
    if (argc != 2){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }

    pid_t pid;
    int i, n = atoi(argv[1]);

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, foo1, &n);
    pthread_create(&thread2, NULL, foo2, &n);
    // int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine) (void *arg), void *arg);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
