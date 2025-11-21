// # Name: Benjamin Banh
// # Date: 10/15/25
// # Title: Lab4 - Step 1

// # Desription: Step 1. [10%] Compile and run this modified threadHello program several times. How many threads complete
// the go function? Explain the program's behavior.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
        printf("Main thread done.\n");
        return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}