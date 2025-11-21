// COEN 146L : Lab 1 - template to use for file transfer (steps 3, 4, and 5)
// You need to adapt this template according to the requirements of each of the steps

/**
 * Name: Benjamin Banh
 * Date: 1/7/25
 * Title: Lab 1: Basic Linux, network commands, and C programming skills
 * Description: review linux commands and write sample C program that demonstrate the use of system calls and files
 * 
 */


#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
// #include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
// #include <sys/mman.h> // mmap()


#define BUF_SIZE 2048 //buffer size


//STEP 3
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

   // reads content of file is loop iterations until end of file
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

    printf("Copied src.dat to dst.dat through func_copy()\n");
   return 0;
}

int main(int argc, char* argv[]) {
   if (argc != 3) {  // check correct usage
       fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
       exit(1);
   }
   //get the source and destination files from the command line arguments
   //call the check copy times function
   func_copy(argv[1], argv[2]);
   return 0;
}
