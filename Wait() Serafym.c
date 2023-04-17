#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Creating a child process.\n");
    fork();
    printf("Waiting while child proces is executed.\n");
    wait(NULL);
    printf("Child process was executed.");
}