#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv){
    size_t mb = (argc>1)?strtoul(argv[1], NULL, 10):200; // MB
    size_t bytes = mb * 1024UL * 1024UL;
    char *buf = malloc(bytes);
    if(!buf){perror("malloc"); return 1;}
    for(size_t i=0;i<bytes;i+=4096) buf[i] = 1; // touch each page
    printf("Allocated & touched %zu MB. PID=%d\n", mb, getpid());
    getchar(); // keep process alive to inspect pmap
    return 0;
}
