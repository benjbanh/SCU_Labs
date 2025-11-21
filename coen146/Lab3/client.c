/*
* Name: Benjamin Banh
* Date: 1/21/2025
* Title: Lab3 - TCP File Transfer Client
* Description: Connects to the server, requests a file, and saves it with a specified name.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <server_ip> <port> <src.dat> <dst.dat>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *src_filename = argv[3];
    char *dst_filename = argv[4];

    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return EXIT_FAILURE;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return EXIT_FAILURE;
    }
    printf("Connected to server %s:%d\n", server_ip, port);

    // Send requested filename
    send(sock, src_filename, strlen(src_filename) + 1, 0);
    printf("Requested file: %s\n", src_filename);

    // Open destination file
    FILE *file = fopen(dst_filename, "wb");
    if (!file) {
        perror("File creation failed");
        close(sock);
        return EXIT_FAILURE;
    }

    // Receive file data
    size_t bytesReceived;
    while ((bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytesReceived, file);
    }

    if (bytesReceived < 0)
        perror("Receive error");

    printf("File received and saved as %s\n", dst_filename);

    fclose(file);
    close(sock);
    return EXIT_SUCCESS;
}


