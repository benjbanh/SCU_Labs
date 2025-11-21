// COEN 146L : Lab 2 - Step 1

/**
 * Name: Benjamin Banh
 * Date: 1/21/25
 * Lab #: Lab 2 Threads and HTTP
 */

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create(), pthread_join(), pthread_exit()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 // buffer size

// data structure to hold copy
struct copy_struct {
    int thread_id; 
    char* src_filename;
    char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
    FILE *src, *dst;
    char* buf;

    src = fopen(src_filename, "r"); 
    if (src == NULL) { 
        fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
        exit(0);
    }
    dst = fopen(dst_filename, "w"); 
    if (dst == NULL) { 
        fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
        exit(0);
    }

    // reads content of file in loop iterations until end of file
    buf = (char*)malloc(BUF_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Error allocating memory for buffer\n");
        exit(1);
    }

    // writes bytes_read to dst_filename
    size_t bytes_read;
    while ((bytes_read = fread(buf, 1, BUF_SIZE, src)) > 0) {
        if (fwrite(buf, 1, bytes_read, dst) != bytes_read) {
            fprintf(stderr, "Error writing to %s\n", dst_filename);
            exit(1);
        }
    }
    // closes src file pointer
    // closes dst file pointer
    // frees memory used for buf
    fclose(src);
    fclose(dst);
    free(buf);
    return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
    struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
    printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
    // call file copy function
    func_copy(params.src_filename, params.dst_filename);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    // check correct usage of arguments in command line
    if (argc < 20) {  
        fprintf(stderr, "usage: %s <n connections> <src1> <dst1> ... <srcN> <dstN>\n", argv[0]);
        exit(1);
    }

    char* src_filename;
    char* dst_filename;
    char* src_filenames[] =  {argv[1], argv[3], argv[5], argv[7], argv[9], argv[11], argv[13], argv[15], argv[17], argv[19]};
    char* dst_filenames[] = {argv[2], argv[4], argv[6], argv[8], argv[10], argv[12], argv[14], argv[16], argv[18], argv[20]};
    int num_threads = 10;

    // Start Time
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();
    
    pthread_t threads[num_threads];
    struct copy_struct thread_params[num_threads];

    int i;
    for (i = 0; i < num_threads; i++) {
        // initialize thread parameters
        thread_params[i].thread_id = i;
        thread_params[i].src_filename = src_filenames[i];
        thread_params[i].dst_filename = dst_filenames[i];
        pthread_create(&threads[i], NULL, copy_thread, (void*)&thread_params[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // End time
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken for multi-threaded copy: %.5f seconds\n", cpu_time_used);

    pthread_exit(NULL);
}
