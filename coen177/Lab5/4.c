// # Name: Benjamin Banh
// # Date: 10/22/25
// # Title: Lab5 - Step 1

// # Desription: Step 4. When employing only mutex locks to coordinate access to a shared buffer between producers and
// consumers, the issue of busy waiting, or spin locking, may arise. To address this, a condition variable is
// utilized as an explicit queue where threads can place themselves when certain conditions of execution
// are not met. This allows threads to wait on the condition, thereby avoiding wasteful busy waiting. A lock
// is employed to facilitate one thread signaling to others that they may proceed if they are waiting for a
// particular condition to be met. Write a C program to illustrate the use of condition variables for
// coordinating the access of the producer and consumer threads to the shared buffer. You may use the
// following pseudo-code for implementation

//Thread Synchronization - Semaphores
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>


#define NTHREADS 10
#define BUFFER_SIZE 10
#define NUM 20

void *go(void *arg);
void cleanup(int sigtype);

void *consume(void *arg);
void *produce(void *arg);

void printArr();

pthread_t threads[NTHREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;

bool is_empty = true;
bool is_full = false;


int head = 0;
int tail = 0;
int* buffer;

int main() {
    buffer = malloc(BUFFER_SIZE * sizeof(int));
    signal(SIGINT,cleanup);

    printArr();
    pthread_create(&threads[0], NULL, produce, NULL);
    pthread_create(&threads[1], NULL, consume, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    return 0;
}

void *consume(void *arg) {
    //Consumer thread
    int val, i;
    for ( i=0;i<NUM;i++) {
        pthread_mutex_lock(&mutex);
        while (is_empty){ // if empty
            pthread_cond_wait(&cond_empty, &mutex);
        }
        
        val = buffer[tail];
        buffer[tail] = 0;
        tail = (tail + 1) % BUFFER_SIZE;
 
        is_full = false;
        if(head == tail)
            is_empty = true;
        
        pthread_cond_broadcast(&cond_full);  // Signal producer
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void *produce(void *arg) {
    int val, i;
    // printf("Hello world");
    for (i=1;i<=NUM;i++) {
        val = i * 10;

        pthread_mutex_lock(&mutex);
        if (is_full){ // if full
            pthread_cond_wait(&cond_full, &mutex);
        }
        
        //add to buffer
        buffer[head] = val;
        head = (head + 1) % BUFFER_SIZE;

        is_empty = false;
        if(head == tail)
            is_full = true;
        
        
        printArr();
        pthread_cond_broadcast(&cond_empty);  // Signal consumer
        pthread_mutex_unlock(&mutex);
        
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
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);
    printf("\n Terminating\n");
    exit(0);
}