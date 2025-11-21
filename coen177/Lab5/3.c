// # Name: Benjamin Banh
// # Date: 10/22/25
// # Title: Lab5 - Step 1

// # Desription: Step 3. Write a program illustrating producer and consumer threads coordinating 
// to access the shared buffer using semaphores. You may use the following pseudo-code.

//Thread Synchronization - Semaphores
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <signal.h>


#define NTHREADS 10
#define BUFFER_SIZE 10
#define NUM 20

void *go(void *arg);
void cleanup(int sigtype);

void *consume(void *arg);
void *produce(void *arg);

void printArr();

pthread_t threads[NTHREADS];
sem_t *mutex;
sem_t *full;
sem_t *empty;

int head = 0;
int tail = 0;
int* buffer;

int main() {
    buffer = malloc(BUFFER_SIZE * sizeof(int));
    signal(SIGINT,cleanup);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    full = sem_open("full", O_CREAT, 0644, 0);
    empty = sem_open("empty", O_CREAT, 0644, BUFFER_SIZE);

    printArr();
    pthread_create(&threads[0], NULL, produce, NULL);
    pthread_create(&threads[1], NULL, consume, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sem_close(mutex);
    sem_close(full);
    sem_close(empty);
    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");


    return 0;
}

void *consume(void *arg) {
    //Consumer thread
    int val, i;
    for ( i=0;i<NUM;i++) {
        // printf("Consuming: ");
        sem_wait(full);
        sem_wait(mutex);
        
        val = buffer[tail];
        buffer[tail] = 0;
        tail = (tail + 1) % BUFFER_SIZE;
        
        sem_post(mutex);
        sem_post(empty);
        // printf("%d\n", val);
    }
    pthread_exit(0);
}

void *produce(void *arg) {
    int val, i;
    // printf("Hello world");
    for (i=1;i<=NUM;i++) {
        val = i * 10;
        // printf("Producing: %d\n", val);

        sem_wait(empty);
        sem_wait(mutex);
        
        buffer[head] = val;
        head = (head + 1) % BUFFER_SIZE;
        
        sem_post(mutex);
        sem_post(full);

        printArr();

        usleep(100000);
    }
    pthread_exit(0);
}

void printArr(){
    for( int i = 0; i < BUFFER_SIZE; i++){
        printf("%d ", buffer[i]);
    }
    // printf("| full: %d  empty: %d\n", full, empty);
    printf("\n");
}

void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}