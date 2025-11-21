/*
* Name: Benjamin Banh
* Date: 1/21/2025
* Title: Lab3 - TCP File Transfer Client
* Description: Server for clients to request a file from. Closes server after each request.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int port = atoi(argv[1]);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connection
    if (listen(server_fd, 1) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server running on port %d...\n", port);

    // Accept a single client
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s:%d\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receive filename request
    char filename[BUFFER_SIZE];
    recv(client_fd, filename, BUFFER_SIZE, 0);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File open failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Send file contents
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_fd, buffer, bytes_read, 0);
    }

    printf("File %s sent successfully.\n", filename);
    fclose(file);
    close(client_fd);
    close(server_fd);  // Server closes after handling one client

    return 0;
}


