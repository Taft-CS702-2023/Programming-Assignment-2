#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define IPC_RESULT_ERROR (-1)

int main()
{
    key_t key;
    key = ftok("test.txt", 0);
    if (key == IPC_RESULT_ERROR)
    {
        return IPC_RESULT_ERROR;
    }

    printf("%d", shmget(key, 4096, 0644 | IPC_CREAT));

}