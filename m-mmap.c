#include <stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
//THIS GIVES A SEGMENTATION FAULT
//but the example code I was referencing also does
//so.
//I don't really know what to do about it.
void main(){
    const char* name = "TEST";
    void* ptr;
    ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_open(name, O_RDONLY, 0666), 0);
    printf("%s", (char*)ptr);
    shm_unlink(name);
}
