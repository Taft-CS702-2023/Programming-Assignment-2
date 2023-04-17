#include <unistd.h>

int main() {
    int fd[2];
    char buf[20];

    pipe(fd); // create a pipe

    if (fork() == 0) {
        // child process
        read(fd[0], buf, sizeof(buf)); // read from pipe
    } else {
        // parent process
        write(fd[1], "Hello, child!", 13); // write to pipe
    }

    return 0;
}