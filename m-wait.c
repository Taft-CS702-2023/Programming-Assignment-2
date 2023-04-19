#include <stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

void main(){
    fork();
    printf("this\n");
    //waits until the child is done with this
    wait(NULL);
    printf("that\n");
}
