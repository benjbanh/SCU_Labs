#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *fp;
FILE *fp_write;
void* foo(void* arg) {
    char* buffer = (char*) arg;
    while (fread(buffer, 1, sizeof(buffer), fp)){
        fwrite(buffer, 1, sizeof(buffer), fp_write);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    fp_write = fopen("test.txt", "w");
    fp = fopen(argv[1], "rb");
    int s = atoi(argv[2]);
    int numThreads = atoi(argv[3]);
    
    char buffer[s];
    pthread_t threads[numThreads];
    
    for(int i = 0; i < numThreads; i++){
        pthread_create(&threads[i], NULL, foo, (void *) buffer );
    }

    for(int j = 0; j < numThreads; j++){
        pthread_join(threads[j], NULL);
    }
    
    fclose(fp);
    fclose(fp_write);
}
