#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid = fork();

    if (pid == -1) {
        printf("fork failed");
        exit(1);
    }
    else if (pid == 0) //child
    { 
        printf("Child process\n");
    }
    else //parent
    {
        wait(NULL); // wait for child (without this line, only the parent prints)
        printf("Parent process\n");
    }
    return 0;
}
