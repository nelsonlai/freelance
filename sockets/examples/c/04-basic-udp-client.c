/*
 * Basic UDP Client
 *
 * A simple UDP client that sends a message to a server.
 * Note: UDP is connectionless, so no connect() call needed.
 *
 * Compile: cc -o 04-basic-udp-client 04-basic-udp-client.c
 * Run:     ./04-basic-udp-client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HOST    "127.0.0.1"
#define PORT    8080
#define BUFSIZE 1024

int main(void) {
    struct sockaddr_in server_addr;
    socklen_t server_len;
    int fd;
    const char *message = "Hello, UDP Server!";
    char buf[BUFSIZE];
    ssize_t n;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(fd);
        return 1;
    }

    printf("Sending to %s:%d: %s\n", HOST, PORT, message);
    if (sendto(fd, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("sendto");
        close(fd);
        return 1;
    }

    server_len = sizeof(server_addr);
    n = recvfrom(fd, buf, sizeof(buf) - 1, 0,
                 (struct sockaddr *)&server_addr, &server_len);
    if (n > 0) {
        buf[n] = '\0';
        printf("Received from %s:%d: %s\n",
               inet_ntoa(server_addr.sin_addr),
               ntohs(server_addr.sin_port),
               buf);
    } else if (n < 0) {
        perror("recvfrom");
        close(fd);
        return 1;
    } else {
        printf("No response received\n");
    }

    close(fd);
    printf("Socket closed\n");
    return 0;
}
