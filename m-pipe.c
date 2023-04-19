#include <stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void main(){
    int channel[2];
    pid_t baby;

    baby = fork();
    pipe(channel);
    if(baby > 0){
        wait(NULL);
        printf("success\n");
        close(channel[0]);
        close(channel[1]);
    }
}
