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


//STEP 4
// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char* src_filename, char* dst_filename)  {
   int src_fd, dst_fd;
   char *buf;

   src_fd = open(src_filename, O_RDONLY);  // opens a file for reading
   if (src_fd < 0) { // open() error checking
       fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
       close(src_fd);
       exit(0);
   }
   // O_WRONLY - write only
   // O_CREAT - create file if it doesn't exist
   // O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
   // opens a file for writing; erases old file/creates a new file
   dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC); 
   if (dst_fd < 0) { // open() error checking
       fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
       close(dst_fd);
       exit(0);
   }

   // read/ write loop
   buf = (char*)malloc((size_t)BUF_SIZE);   
   if (buf == NULL) {
        fprintf(stderr, "Error allocating memory for buffer\n");
        exit(1);
   }
   // reads up to BUF_SIZE bytes from src_filename
   // writes bytes_read to dst_filename

    size_t bytes_read;
    while ((bytes_read = read(src_fd, buf, BUF_SIZE)) > 0) {
        if (write(dst_fd, buf, bytes_read) != bytes_read) {
            fprintf(stderr, "Error writing to %s\n", dst_filename);
            exit(1);
        }
    }
    if (bytes_read < 0) {
        fprintf(stderr, "Error reading from %s\n", src_filename);
        exit(1);
    }

  
   // closes src_fd file descriptor
   // closes dst_fd file descriptor
   // frees memory used for buf
    close(src_fd);
    close(dst_fd);
    free(buf);

    printf("Copied src.dat to dst.dat through syscall_copy()\n");


   return 0;
}


int main(int argc, char* argv[]) {
   if (argc != 3) {  // check correct usage
       fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
       exit(1);
   }
   //get the source and destination files from the command line arguments
   //call the check copy times function
   syscall_copy(argv[1], argv[2]);
   return 0;
}
