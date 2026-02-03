/**
 * Solution 13.2: Process Monitor Utility
 * Week 13 - System Programming Basics
 * 
 * Description: Process monitor utility
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t keep_running = 1;

void signal_handler(int sig) {
    keep_running = 0;
}

void print_process_info(pid_t pid, const char* command) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    printf("[%ld.%06ld] Process %d (%s) ", 
           tv.tv_sec, tv.tv_usec, pid, command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }
    
    signal(SIGINT, signal_handler);
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    
    if (pid == 0) {
        // Child process - execute the command
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        return 1;
    } else {
        // Parent process - monitor the child
        print_process_info(pid, argv[1]);
        printf("started\n");
        
        int status;
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        
        // Monitor process
        while (keep_running) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            
            if (result == pid) {
                // Process has terminated
                gettimeofday(&end_time, NULL);
                
                double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                               (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
                
                print_process_info(pid, argv[1]);
                
                if (WIFEXITED(status)) {
                    printf("exited with status %d after %.3f seconds\n", 
                           WEXITSTATUS(status), elapsed);
                } else if (WIFSIGNALED(status)) {
                    printf("terminated by signal %d after %.3f seconds\n", 
                           WTERMSIG(status), elapsed);
                }
                break;
            } else if (result == -1) {
                perror("waitpid failed");
                break;
            }
            
            // Sleep for a short time before checking again
            usleep(100000); // 100ms
        }
        
        if (!keep_running) {
            // Interrupted by signal, kill child process
            kill(pid, SIGTERM);
            waitpid(pid, &status, 0);
            print_process_info(pid, argv[1]);
            printf("terminated by user\n");
        }
    }
    
    return 0;
}