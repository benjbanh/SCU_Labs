// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 8

// # Desription: Step 8. [15%] What is the fix for the program bug in Step 7? Write a program to demonstrate your fix.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++){
        sleep(0.01);
        pthread_create(&threads[i], NULL, go, &i);
    }
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long) pthread_self(), *(int *)arg);
    sleep(1);
    return 0;
}