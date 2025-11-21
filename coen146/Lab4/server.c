/* 
* Name: Benjamin Banh
* Date: 2/4/2025
* Title: Lab4 - Part 1 (UDP)
* Description: Server to receive a file from a client and save it to the specified destination file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define EOF_SIGNAL "EOF"  // Special message to indicate end of file

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <dst file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int port = atoi(argv[1]);
    char *dst_filename = argv[2];

    // Create UDP socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server running on port %d...\n", port);

    // Prepare to receive file data from client
    char buffer[BUFFER_SIZE];
    FILE *dst_file = fopen(dst_filename, "wb");
    if (!dst_file) {
        perror("File open failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    ssize_t recv_len;
    while (1) {
        recv_len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr *)&client_addr, &client_len);
        if (recv_len == -1) {
            perror("recvfrom failed");
            fclose(dst_file);
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Check if it's EOF signal
        if (recv_len == strlen(EOF_SIGNAL) && strncmp(buffer, EOF_SIGNAL, recv_len) == 0) {
            printf("End of file received.\n");
            break; // End of file
        }

        // Write received data to the destination file
        if (fwrite(buffer, 1, recv_len, dst_file) != recv_len) {
            perror("File write failed");
            fclose(dst_file);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    printf("File received successfully and saved as %s\n", dst_filename);
    fclose(dst_file);
    close(server_fd);

    return 0;
}


