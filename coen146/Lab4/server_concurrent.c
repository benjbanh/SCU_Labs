/*
* Name: Benjamin Banh
* Date: 2/4/2025
* Title: Lab4 - Part 1 (UDP) - Multithreaded Server
* Description: A server that receives a file from a client using UDP and handles multiple clients concurrently using threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define EOF_SIGNAL "EOF"  // Special message to indicate end of file

void *handle_client(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <dst file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int server_fd;
    struct sockaddr_in server_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);
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

    // Receive messages from clients and handle them in separate threads
    while (1) {
        struct sockaddr_in client_addr;
        pthread_t tid;

        // Receive client message (file data request)
        char filename[BUFFER_SIZE];
        int recv_len = recvfrom(server_fd, filename, BUFFER_SIZE, 0,
                                (struct sockaddr *)&client_addr, &client_len);
        if (recv_len == -1) {
            perror("recvfrom failed");
            continue;
        }

        filename[recv_len] = '\0';  // Null-terminate filename string
        printf("Received file request: %s\n", filename);

        // Allocate memory for client address
        struct sockaddr_in *client_info = malloc(sizeof(struct sockaddr_in));
        memcpy(client_info, &client_addr, sizeof(struct sockaddr_in));

        // Create a new thread to handle this client
        pthread_create(&tid, NULL, handle_client, client_info);
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}

// Thread function to handle file transfer
void *handle_client(void *arg) {
    struct sockaddr_in *client_addr = (struct sockaddr_in *)arg;
    free(arg);  // Free memory allocated for client address

    int server_fd;
    struct sockaddr_in server_addr;
    socklen_t client_len = sizeof(*client_addr);

    // Create UDP socket for client communication
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket failed");
        return NULL;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(0);  // Let the OS pick an available port

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    FILE *dst_file = fopen("received_file", "wb");  // File to store received data
    if (!dst_file) {
        perror("File open failed");
        close(server_fd);
        return NULL;
    }

    ssize_t recv_len;
    while (1) {
        recv_len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr *)client_addr, &client_len);
        if (recv_len == -1) {
            perror("recvfrom failed");
            fclose(dst_file);
            close(server_fd);
            return NULL;
        }

        // Check if it's EOF signal
        if (recv_len == strlen(EOF_SIGNAL) && strncmp(buffer, EOF_SIGNAL, recv_len) == 0) {
            printf("End of file received.\n");
            break;  // End of file
        }

        // Write received data to the destination file
        if (fwrite(buffer, 1, recv_len, dst_file) != recv_len) {
            perror("File write failed");
            fclose(dst_file);
            close(server_fd);
            return NULL;
        }
    }

    printf("File received successfully and saved as received_file\n");
    fclose(dst_file);
    close(server_fd);
    return NULL;
}


