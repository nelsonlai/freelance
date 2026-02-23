/*
 * Basic TCP Echo Server
 *
 * A simple TCP server that echoes back whatever it receives.
 * This is the simplest possible TCP server implementation.
 *
 * Compile: cc -o 01-basic-tcp-server 01-basic-tcp-server.c
 * Run:     ./01-basic-tcp-server
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
    struct sockaddr_in addr;
    int opt = 1;
    char buf[BUFSIZE];
    ssize_t n;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SO_REUSEADDR");
        close(server_fd);
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
    printf("Server bound to %s:%d\n", HOST, PORT);

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }
    printf("Server listening on %s:%d...\n", HOST, PORT);
    printf("Press Ctrl+C to stop\n");

    signal(SIGINT, cleanup);

    for (;;) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd;

        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        printf("\nConnection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        n = recv(client_fd, buf, sizeof(buf) - 1, 0);
        if (n > 0) {
            buf[n] = '\0';
            printf("Received: %s\n", buf);
            if (send(client_fd, buf, (size_t)n, 0) < 0)
                perror("send");
            else
                printf("Echoed: %s\n", buf);
        } else if (n == 0) {
            printf("Client closed connection\n");
        } else {
            perror("recv");
        }

        close(client_fd);
        printf("Connection closed\n");
    }

    /* unreachable when loop runs forever */
    close(server_fd);
    return 0;
}
