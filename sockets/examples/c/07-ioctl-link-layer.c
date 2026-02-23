/*
 * ioctl() and the Link-Layer Driver
 *
 * Shows how to use ioctl() on a socket to query the kernel's network
 * interface (link-layer) driver. Uses SIOCGIFCONF to list interfaces,
 * then SIOCGIFFLAGS, SIOCGIFHWADDR (MAC), SIOCGIFMTU, and SIOCGIFADDR
 * per interface.
 *
 * Link-layer ioctls use struct ifreq / struct ifconf and the net device
 * ioctl codes (see netdevice(7) on Linux). The same socket is used only
 * as a handle for ioctl(); no packets are sent.
 *
 * Linux-oriented (SIOCGIFHWADDR is Linux-specific). macOS/BSD use
 * getifaddrs() for MAC and some other data.
 *
 * Compile (Linux): cc -o 07-ioctl-link-layer 07-ioctl-link-layer.c
 * Run:             ./07-ioctl-link-layer [interface-name]
 *                  (no argument = list all interfaces)
 *
 * May require CAP_NET_ADMIN or root for some ioctls on restricted interfaces.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef SIOCGIFHWADDR
/* Not defined on macOS/BSD */
#define SIOCGIFHWADDR 0x8927
#endif

#define IFLIST_SIZE  (128 * sizeof(struct ifreq))

static void print_mac(unsigned char *data) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           data[0], data[1], data[2], data[3], data[4], data[5]);
}

static void list_one(int fd, const char *ifname) {
    struct ifreq ifr;
    struct sockaddr_in *sin;
    char addr_buf[INET_ADDRSTRLEN];

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';

    printf("Interface: %s\n", ifr.ifr_name);

    if (ioctl(fd, SIOCGIFFLAGS, &ifr) == 0) {
        printf("  Flags:  %s%s%s\n",
               (ifr.ifr_flags & IFF_UP)      ? "UP "   : "",
               (ifr.ifr_flags & IFF_RUNNING) ? "RUNNING " : "",
               (ifr.ifr_flags & IFF_LOOPBACK) ? "LOOPBACK" : "");
    }

#ifdef __linux__
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0) {
        unsigned char *hw = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        printf("  MAC:    ");
        print_mac(hw);
        printf("\n");
    }
#else
    (void)print_mac;
    printf("  MAC:    (use getifaddrs on this platform)\n");
#endif

    if (ioctl(fd, SIOCGIFMTU, &ifr) == 0)
        printf("  MTU:    %d\n", ifr.ifr_mtu);

    if (ioctl(fd, SIOCGIFADDR, &ifr) == 0) {
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
        if (sin->sin_family == AF_INET && inet_ntop(AF_INET, &sin->sin_addr, addr_buf, sizeof(addr_buf)))
            printf("  IPv4:   %s\n", addr_buf);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    struct ifconf ifc;
    struct ifreq *ifr;
    char *buf;
    int fd;
    int i, n;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    buf = malloc(IFLIST_SIZE);
    if (!buf) {
        perror("malloc");
        close(fd);
        return 1;
    }

    memset(&ifc, 0, sizeof(ifc));
    ifc.ifc_len = IFLIST_SIZE;
    ifc.ifc_buf = buf;

    if (ioctl(fd, SIOCGIFCONF, &ifc) < 0) {
        perror("ioctl SIOCGIFCONF");
        free(buf);
        close(fd);
        return 1;
    }

    ifr = ifc.ifc_req;
    n = ifc.ifc_len / sizeof(struct ifreq);

    if (argc >= 2) {
        /* Query a single interface by name */
        list_one(fd, argv[1]);
    } else {
        /* List all interfaces */
        for (i = 0; i < n; i++)
            list_one(fd, ifr[i].ifr_name);
    }

    free(buf);
    close(fd);
    return 0;
}
