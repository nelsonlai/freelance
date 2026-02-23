/*
 * Basic HTTPS Client
 *
 * Connects to an HTTPS server (port 443), performs the TLS handshake,
 * and sends an HTTP GET request. Demonstrates TCP + TLS + HTTP as in
 * "How HTTPS Talks" (10-security/02-https-how-it-works.md).
 *
 * Requires OpenSSL (libssl, libcrypto). Build:
 *
 *   Linux:
 *     cc -o 05-https-client 05-https-client.c -lssl -lcrypto
 *
 *   macOS (Homebrew OpenSSL, adjust path for your arch):
 *     cc -I$(brew --prefix openssl)/include -L$(brew --prefix openssl)/lib \
 *        -o 05-https-client 05-https-client.c -lssl -lcrypto
 *
 * Run:
 *   ./05-https-client www.example.com
 *   ./05-https-client www.example.com /
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT_HTTPS 443
#define BUFSIZE    4096

static void ssl_err(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    ERR_print_errors_fp(stderr);
}

int main(int argc, char *argv[]) {
    const char *hostname, *path;
    struct addrinfo hints, *res, *rp;
    int fd = -1;
    int ret;
    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;
    char request[1024];
    char buf[BUFSIZE];
    int n;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <hostname> [path]\n", argv[0]);
        fprintf(stderr, "Example: %s www.example.com /\n", argv[0]);
        return 1;
    }
    hostname = argv[1];
    path = (argc >= 3) ? argv[2] : "/";

    /* Resolve hostname to IP */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    ret = getaddrinfo(hostname, "443", &hints, &res);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    for (rp = res; rp != NULL; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd < 0)
            continue;
        if (connect(fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(res);
    if (fd < 0) {
        perror("connect");
        return 1;
    }

    printf("TCP connected to %s:443\n", hostname);

    /* TLS setup */
    ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        ssl_err("SSL_CTX_new failed");
        close(fd);
        return 1;
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    if (!SSL_CTX_set_default_verify_paths(ctx)) {
        ssl_err("SSL_CTX_set_default_verify_paths failed");
        SSL_CTX_free(ctx);
        close(fd);
        return 1;
    }

#if defined(TLS1_2_VERSION)
    if (!SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION)) {
        fprintf(stderr, "SSL_CTX_set_min_proto_version failed\n");
        SSL_CTX_free(ctx);
        close(fd);
        return 1;
    }
#endif

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        ssl_err("SSL_new failed");
        SSL_CTX_free(ctx);
        close(fd);
        return 1;
    }

    SSL_set_fd(ssl, fd);

    if (!SSL_set_tlsext_host_name(ssl, hostname)) {
        ssl_err("SSL_set_tlsext_host_name (SNI) failed");
        goto fail;
    }
    if (!SSL_set1_host(ssl, hostname)) {
        ssl_err("SSL_set1_host failed");
        goto fail;
    }

    /* TLS handshake */
    if (SSL_connect(ssl) <= 0) {
        ssl_err("SSL_connect failed");
        if (SSL_get_verify_result(ssl) != X509_V_OK)
            fprintf(stderr, "Verify error: %s\n",
                    X509_verify_cert_error_string(SSL_get_verify_result(ssl)));
        goto fail;
    }
    printf("TLS handshake done (server certificate verified)\n");

    /* HTTP GET over TLS */
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n"
             "\r\n",
             path, hostname);

    if (SSL_write(ssl, request, (int)strlen(request)) <= 0) {
        ssl_err("SSL_write failed");
        goto fail;
    }
    printf("Sent HTTP request for %s\n\n", path);

    /* Read response */
    printf("Response:\n");
    while ((n = SSL_read(ssl, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        fputs(buf, stdout);
    }
    if (n < 0) {
        ssl_err("SSL_read error");
        goto fail;
    }
    printf("\n");

    SSL_shutdown(ssl);
    ret = 0;
fail:
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(fd);
    return ret;
}
