/*
 * Basic TCP Client
 *
 * A simple TCP client that connects to a server and sends a message.
 *
 * Compile: cc -o 02-basic-tcp-client 02-basic-tcp-client.c
 * Run:     ./02-basic-tcp-client
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
    int fd;
    const char *message = "Hello, Server!";
    char buf[BUFSIZE];
    ssize_t n;

    fd = socket(AF_INET, SOCK_STREAM, 0);
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

    printf("Connecting to %s:%d...\n", HOST, PORT);
    if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        fprintf(stderr, "Make sure the server is running on %s:%d\n", HOST, PORT);
        close(fd);
        return 1;
    }
    printf("Connected!\n");

    printf("Sending: %s\n", message);
    if (send(fd, message, strlen(message), 0) < 0) {
        perror("send");
        close(fd);
        return 1;
    }

    n = recv(fd, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("Received: %s\n", buf);
    } else if (n == 0) {
        printf("Server closed connection\n");
    } else {
        perror("recv");
        close(fd);
        return 1;
    }

    close(fd);
    printf("Connection closed\n");
    return 0;
}
