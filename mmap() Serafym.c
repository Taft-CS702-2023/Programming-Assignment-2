#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    uint8_t* first = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    uint8_t* second = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

    printf("First: %d\n", first);
    printf("Second: %d", second);
}