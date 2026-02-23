/*
 * Domain Name to IP Address Lookup
 *
 * Shows how a domain name (e.g. "www.example.com") is translated to
 * IP address(es) using the system resolver (DNS). Uses getaddrinfo()
 * for a portable, IPv4/IPv6-aware lookup.
 *
 * Compile: cc -o 06-domain-to-ip 06-domain-to-ip.c
 * Run:     ./06-domain-to-ip www.example.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    const char *hostname;
    struct addrinfo hints, *res, *rp;
    int ret;
    char ipstr[INET6_ADDRSTRLEN];
    void *addr_ptr;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <domain-name>\n", argv[0]);
        fprintf(stderr, "Example: %s www.example.com\n", argv[0]);
        return 1;
    }
    hostname = argv[1];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     /* IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* not used for address-only lookup */

    ret = getaddrinfo(hostname, NULL, &hints, &res);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    printf("Domain: %s\n", hostname);
    printf("Resolved to:\n");

    for (rp = res; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *in4 = (struct sockaddr_in *)rp->ai_addr;
            addr_ptr = &in4->sin_addr;
        } else if (rp->ai_family == AF_INET6) {
            struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr_ptr = &in6->sin6_addr;
        } else {
            continue;
        }
        inet_ntop(rp->ai_family, addr_ptr, ipstr, sizeof(ipstr));
        printf("  %s (%s)\n", ipstr,
               rp->ai_family == AF_INET ? "IPv4" : "IPv6");
    }

    freeaddrinfo(res);
    return 0;
}
