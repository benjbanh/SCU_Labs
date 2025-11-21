/* 
* Name: Benjamin Banh
* Date: 2/4/2025
* Title: Lab4 - Part 2 (UDP)
* Description: Client to send a file to a server and save it to the specified destination file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define EOF_SIGNAL "EOF"

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
   char buffer[BUFFER_SIZE];

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

   // Send a connection request message (any simple message to indicate readiness)
   const char *message = "Ready to send file";
   if (sendto(sock, message, strlen(message) + 1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
       perror("Send failed");
       close(sock);
       return EXIT_FAILURE;
   }
   printf("Sent connection request to server: %s\n", message);

   // Open source file to send
   FILE *file = fopen(src_filename, "rb");
   if (!file) {
       perror("File open failed");
       close(sock);
       return EXIT_FAILURE;
   }

   // Send file data to server
   size_t bytes_read;
   while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
       if (sendto(sock, buffer, bytes_read, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
           perror("Send failed");
           fclose(file);
           close(sock);
           return EXIT_FAILURE;
       }
   }

   // Send EOF signal to server
   sendto(sock, EOF_SIGNAL, strlen(EOF_SIGNAL), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

   printf("File %s sent successfully.\n", src_filename);

   fclose(file);
   close(sock);

   return EXIT_SUCCESS;
}



