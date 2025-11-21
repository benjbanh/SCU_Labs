/*
* Name: Benjamin Banh
* Date: 2/11/2025
* Title: Lab5 - Stop and Wait for an Unreliable Channel with Error and Loss
* Description: Client to send a file to a server using Stop and Wait protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <sys/select.h> // Include this header for select() and fd_set

#define BUFFER_SIZE 100
#define TIMEOUT 2 // Timeout in seconds

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


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <server_ip> <port> <src file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *src_filename = argv[3];

    int sock;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        return EXIT_FAILURE;
    }

    // Open source file to send
    FILE *file = fopen(src_filename, "rb");
    if (!file) {
        perror("File open failed");
        close(sock);
        return EXIT_FAILURE;
    }

    int seq_num = 0;
    size_t bytes_read;
    char buffer[BUFFER_SIZE];
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        Packet packet;
        packet.seq_ack = seq_num;
        packet.len = bytes_read;
        memcpy(packet.data, buffer, bytes_read);
        packet.checksum = 0;
        packet.checksum = calculate_checksum(packet);

        int ack_received = 0;
        while (!ack_received) {
            // Send packet
            if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&server_addr, addr_len) == -1) {
                perror("Send failed");
                fclose(file);
                close(sock);
                return EXIT_FAILURE;
            }
            printf("Sent packet with seq_num %d\n", seq_num);

            // Set up select for timeout
            struct timeval tv;
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(sock, &readfds);
            tv.tv_sec = TIMEOUT;
            tv.tv_usec = 0;

            int rv = select(sock + 1, &readfds, NULL, NULL, &tv);
            if (rv == 0) {
                // Timeout, resend packet
                printf("Timeout, resending packet with seq_num %d\n", seq_num);
            } else if (rv == -1) {
                perror("Select failed");
                fclose(file);
                close(sock);
                return EXIT_FAILURE;
            } else {
                // Receive ACK
                Packet ack_packet;
                ssize_t bytes_received = recvfrom(sock, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr *)&server_addr, &addr_len);
                if (bytes_received < 0) {
                    perror("Receive failed");
                    fclose(file);
                    close(sock);
                    return EXIT_FAILURE;
                }

                // Verify checksum
                int received_checksum = ack_packet.checksum;
                ack_packet.checksum = 0;
                int calculated_checksum = calculate_checksum(ack_packet);
                if (received_checksum != calculated_checksum) {
                    printf("Checksum error. ACK discarded. Received: %d, Calculated: %d\n", received_checksum, calculated_checksum);
                    continue;
                }

                // Check sequence number
                if (ack_packet.seq_ack == seq_num) {
                    ack_received = 1;
                    seq_num = !seq_num; // Toggle sequence number
                } else {
                    printf("Unexpected ACK sequence number. ACK discarded. Expected: %d, Received: %d\n", seq_num, ack_packet.seq_ack);
                }
            }
        }
    }

    // Send EOF signal to server
    Packet eof_packet;
    eof_packet.seq_ack = seq_num;
    eof_packet.len = 0;
    eof_packet.checksum  = 0;
    eof_packet.checksum = calculate_checksum(eof_packet);
    for (int i = 0; i < 3; i++) {
        if (sendto(sock, &eof_packet, sizeof(eof_packet), 0, (struct sockaddr *)&server_addr, addr_len) == -1) {
            perror("Send EOF failed");
            fclose(file);
            close(sock);
            return EXIT_FAILURE;
        }
        printf("Sent EOF packet with seq_num %d\n", seq_num);

        // Set up select for timeout
        struct timeval tv;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;

        int rv = select(sock + 1, &readfds, NULL, NULL, &tv);
        if (rv == 0) {
            // Timeout, resend EOF
            printf("Timeout, resending EOF packet\n");
        } else if (rv == -1) {
            perror("Select failed");
            fclose(file);
            close(sock);
            return EXIT_FAILURE;
        } else {
            // Receive ACK
            Packet ack_packet;
            ssize_t bytes_received = recvfrom(sock, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr *)&server_addr, &addr_len);
            if (bytes_received < 0) {
                perror("Receive failed");
                fclose(file);
                close(sock);
                return EXIT_FAILURE;
            }

            // Verify checksum
            int received_checksum = ack_packet.checksum;
            ack_packet.checksum = 0;
            int calculated_checksum = calculate_checksum(ack_packet);
            if (received_checksum != calculated_checksum) {
                printf("Checksum error. ACK discarded. Received: %d, Calculated: %d\n", received_checksum, calculated_checksum);
                continue;
            }

            // Check sequence number
            if (ack_packet.seq_ack == seq_num) {
                break;
            } else {
                printf("Unexpected ACK sequence number. ACK discarded. Expected: %d, Received: %d\n", seq_num, ack_packet.seq_ack);
            }
        }
    }

    printf("File %s sent successfully.\n", src_filename);

    fclose(file);
    close(sock);

    return EXIT_SUCCESS;
}


