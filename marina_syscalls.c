//shmget, mmap
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

void alarm_handler(int signum){
	printf("alarm\n");
	return;
}

int main(){
	pid_t pid;
	pid = fork();
	int status, size;
	char buffer[50];
	char *data;
	int fd[2];
	int fdmap;	

	if (pipe(fd) == -1){
		perror("pipe");
		exit(1); //what a fail gosh darn
	}

	data = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fdmap, 0);
	if(data == MAP_FAILED){
		perror("mmap");
		exit(1);
	}	
	printf("Here's what your file says:\n%s", data);

	key_t key = ftok(".", 'R');
	if (key == -1){
		perror("ftok");
		exit(1);
	}
	
	int shmid = shmget(key, 1024, IPC_CREAT | 0666); 
	//1024 bytes of r&w for everyone
	if (shmid == -1) {
        	perror("shmget");
        	exit(1);
    	}

	int *shm_ptr = (int *)shmat(shmid, NULL, 0);
	if (shm_ptr == (int *)(-1)) {
        	perror("shmat");
        	exit(1);
    	}	

	if(pid == -1){
		perror("fork");
		return 1;
	} else if(pid == 0){
		printf("child process id: %d\n", getpid());
		sleep(5);
		close(fd[0]);
		write(fd[1], "are you my mom?", 15);
		printf("child slept and is now awake");
		return 0;
	} else {
		printf("parent process id: %d, child PID: %d\n", getpid(), pid);
		wait(&status);
		printf("parent process: alarm clock went off\n");
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf("wow we got mail: %s\n", buffer);
		close(fd[0]);
		return 0;
	}
}
