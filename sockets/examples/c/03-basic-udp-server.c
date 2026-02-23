/*
 * Basic UDP Echo Server
 *
 * A simple UDP server that echoes back whatever it receives.
 * Note: UDP is connectionless, so no accept() or connect() calls.
 *
 * Compile: cc -o 03-basic-udp-server 03-basic-udp-server.c
 * Run:     ./03-basic-udp-server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HOST    "127.0.0.1"
#define PORT    8080
#define BUFSIZE 1024

static int server_fd = -1;

static void cleanup(int sig) {
    (void)sig;
    if (server_fd >= 0) {
        printf("\n\nShutting down server...\n");
        close(server_fd);
        server_fd = -1;
        exit(0);
    }
}

int main(void) {
    struct sockaddr_in addr, client_addr;
    socklen_t client_len;
    char buf[BUFSIZE];
    char response[BUFSIZE + 8];  /* "Echo: " + message */
    ssize_t n;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(server_fd);
        return 1;
    }

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }
    printf("UDP server listening on %s:%d...\n", HOST, PORT);
    printf("Press Ctrl+C to stop\n");

    signal(SIGINT, cleanup);

    for (;;) {
        client_len = sizeof(client_addr);
        n = recvfrom(server_fd, buf, sizeof(buf) - 1, 0,
                     (struct sockaddr *)&client_addr, &client_len);
        if (n < 0) {
            perror("recvfrom");
            continue;
        }
        buf[n] = '\0';

        printf("Received from %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port),
               buf);

        (void)snprintf(response, sizeof(response), "Echo: %s", buf);
        if (sendto(server_fd, response, strlen(response), 0,
                   (struct sockaddr *)&client_addr, client_len) < 0)
            perror("sendto");
        else
            printf("Echoed to %s:%d\n",
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
    }

    close(server_fd);
    return 0;
}
