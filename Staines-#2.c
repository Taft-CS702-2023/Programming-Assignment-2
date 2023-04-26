#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define SHM_SIZE 1024

int main()
{
  int pid, status, fd[2], shmid;
  char *shmaddr;
  
  // create a pipe
  if (pipe(fd) < 0)
  {
    perror("pipe");
    exit(1);
  }
    
  // fork a child process
  pid = fork();
  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0) // child process
  {
    close(fd[0]); // close the read end of the pipe
        
    // write a message to the parent process through the pipe
    char *msg = "Hello parent process!";
    write(fd[1], msg, sizeof(msg));
        
    exit(0);
  }
  else // parent process
  {
    close(fd[1]); // close the write end of the pipe
        
    // read the message sent by the child process from the pipe
    char buffer[1024];
    read(fd[0], buffer, sizeof(buffer));
    printf("Message received from child process: %s\n", buffer);
        
    // create a shared memory segment
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
      perror("shmget");
      exit(1);
    }
        
    //attach the shared memory segment to the parent process's address space
    shmaddr = (char *) mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, 
    MAP_SHARED, shmid, 0);
    if (shmaddr == MAP_FAILED)
    {
      perror("mmap");
      exit(1);
    }
        
    // write a message to the shared memory segment
    char *msg = "Hello shared memory!";
    sprintf(shmaddr, "%s", msg);
        
    // wait for the child process to finish
    wait(&status);
  }
    
  // clean up the shared memory segment
  munmap(shmaddr, SHM_SIZE);
  shmctl(shmid, IPC_RMID, NULL);
    
  return 0;
}

