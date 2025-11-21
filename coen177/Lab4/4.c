// # Name: Benjamin Banh
// # Date: 10/15/25
// # Title: Lab4 - Step 4

// # Desription: Step 4. [40%] Write a program that implements matrix multiplication in a multi-threaded environment.
#include <pthread.h>
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   
#include <unistd.h>
#include <stdbool.h>
#define N 2


//N threads (in main)
pthread_t threads[N];
double **matrixA, **matrixB, **matrixC;

//function prototypes
int main(int argc,char *argv[]); //read N, M, and L as command-line arguments
double **initializeMatrix(int r,int c, double **matrix, bool fillRand); //initialize matrix with random values
void printMatrix(int r,int c, double **matrix); //print matrix
void *multiplyRow(void* arg); //thread multiply function

//initialize matrix with random values
double **initializeMatrix(int r,int c, double **matrix, bool fillRand){
    matrix = malloc(r * sizeof(double *));
    for (int i = 0; i < r; i++)
        matrix[i] = malloc(c * sizeof(double));

    if(fillRand){
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                matrix[i][j] = rand() % 10;
    }
    return matrix;
}

//print matrix
void printMatrix(int r,int c, double **matrix){

    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            printf("%.2f\t", matrix[i][j]);
        printf("\n");
    }
    printf("\n");

}
//thread multiply function
void *multiplyRow(void *arg) {
    int row = *(int *)arg;

    for (int j = 0; j < N; j++) {
        matrixC[row][j] = matrixA[row][j] * matrixB[row][j];
    }

    pthread_exit(0);
}

int main(int argc,char *argv[]){
    int i, j, k;
    srand(time(NULL));

    // printf("Hello World");
    matrixA = initializeMatrix(N, N, matrixA, true);
    matrixB = initializeMatrix(N, N, matrixB, true);

    printf("MatrixA: \n");
    printMatrix(N, N, matrixA);
    
    printf("MatrixB: \n");
    printMatrix(N, N, matrixB);
    
    matrixC = initializeMatrix(N, N, matrixC, false);
    // printMatrix(N, N, matrixC);

    // create threads
    int rowIndices[N];
    for (int i = 0; i < N; i++) {
        rowIndices[i] = i;
        pthread_create(&threads[i], NULL, multiplyRow, &rowIndices[i]);
    }

    // wait for threads to finish
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("MatrixC:\n");
    printMatrix(N, N, matrixC);
}