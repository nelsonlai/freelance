#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    size_t sz = 100UL<<20; // 100MB
    void *p = malloc(sz);
    if(!p){perror("malloc"); return 1;}
    if(mlock(p, sz)!=0){perror("mlock");}
    printf("Locked 100MB. Check VmLck in /proc/%d/status\n", getpid());
    getchar();
}
