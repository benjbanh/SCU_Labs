// # Name: Benjamin Banh
// # Date: 10/8/25
// # Title: Lab3 - Step 1

// # Desription: Step 1. [10%] Compile and run the following program and write your observations. Then, modify it to pass the -l
// option to the ls command

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//main
int main() {
    int fds[2];

    pipe(fds);
    /*child 1 redirects stdin to downstream of pipe (read)*/
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0);
    }
    /*child 2 redirects stdout to upstream of pipe (write) */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        // execlp("ls", "ls", 0);
        execlp("ls", "ls", "-l", (char *)0);
    }
    else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
