/*
* Name: Benjamin Banh
* Date: 2/11/2025
* Title: Lab5 - Stop and Wait for an Unreliable Channel with Error and Loss
* Description: Server to receive a file from a client using Stop and Wait protocol and save it to the specified destination file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>


#define BUFFER_SIZE 100


typedef struct {
    int seq_ack;
    int len;
    int checksum;
    char data[BUFFER_SIZE];
} Packet;


int calculate_checksum(Packet packet) {
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Packet);
    while (ptr < end) {
        checksum ^= *ptr++;
    }
    return checksum;
}


void send_ack(int sockfd, struct sockaddr_in *client_addr, socklen_t client_len, int seq_ack) {
    Packet ack_packet;
    ack_packet.seq_ack = seq_ack;
    ack_packet.len = 0;
    ack_packet.checksum = 0;
    ack_packet.checksum = calculate_checksum(ack_packet);
    sendto(sockfd, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr *)client_addr, client_len);
    printf("Sent ACK for seq_ack %d\n", seq_ack);
}


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
    FILE *dst_file = fopen(dst_filename, "wb");
    if (!dst_file) {
        perror("File open failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }


    Packet packet;
    int expected_seq = 0;
    while (1) {
        ssize_t recv_len = recvfrom(server_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&client_addr, &client_len);
        if (recv_len == -1) {
            perror("recvfrom failed");
            fclose(dst_file);
            close(server_fd);
            exit(EXIT_FAILURE);
        }


        // Verify checksum
        int received_checksum = packet.checksum;
        packet.checksum = 0;
        int calculated_checksum = calculate_checksum(packet);
        if (received_checksum != calculated_checksum) {
            printf("Checksum error. Packet discarded. Received: %d, Calculated: %d\n", received_checksum, calculated_checksum);
            send_ack(server_fd, &client_addr, client_len, !expected_seq);
            continue;
        }


        // Check sequence number
        if (packet.seq_ack != expected_seq) {
            printf("Unexpected sequence number. Packet discarded. Expected: %d, Received: %d\n", expected_seq, packet.seq_ack);
            send_ack(server_fd, &client_addr, client_len, !expected_seq);
            continue;
        }


        // Check if it's the end of file
        if (packet.len == 0) {
            printf("End of file received.\n");
            send_ack(server_fd, &client_addr, client_len, expected_seq);
            break;
        }


        // Write received data to the destination file
        if (fwrite(packet.data, 1, packet.len, dst_file) != packet.len) {
            perror("File write failed");
            fclose(dst_file);
            close(server_fd);
            exit(EXIT_FAILURE);
        }


        // Send ACK
        send_ack(server_fd, &client_addr, client_len, expected_seq);
        expected_seq = !expected_seq;
    }


    printf("File received successfully and saved as %s\n", dst_filename);
    fclose(dst_file);
    close(server_fd);


    return 0;
}



