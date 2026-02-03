/**
 * Solution 13.1: File Copy Using System Calls
 * Week 13 - System Programming Basics
 * 
 * Description: File copy using system calls
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        fprintf(stderr, "Error opening source file '%s': %s\n", 
                argv[1], strerror(errno));
        return 1;
    }
    
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        fprintf(stderr, "Error getting source file stats: %s\n", strerror(errno));
        close(src_fd);
        return 1;
    }
    
    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
    if (dst_fd == -1) {
        fprintf(stderr, "Error creating destination file '%s': %s\n", 
                argv[2], strerror(errno));
        close(src_fd);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    off_t total_bytes = 0;
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error writing to destination file: %s\n", 
                    strerror(errno));
            close(src_fd);
            close(dst_fd);
            return 1;
        }
        total_bytes += bytes_written;
    }
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading from source file: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }
    
    close(src_fd);
    close(dst_fd);
    
    printf("Successfully copied %ld bytes from '%s' to '%s'\n", 
           total_bytes, argv[1], argv[2]);
    
    return 0;
}