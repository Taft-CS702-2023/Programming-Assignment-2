# Programming-Assignment-2
More system calls
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
   if(fork()==0)
   {
     printf("Hello World");
   }
   else
   {
     printf("hello world leaders");
     wait(NULL);
     printf("Hello WORLD");
   }


   return 0;
}


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 int main(){
   int A=5;
   int *ptr = mmap ( NULL, A*sizeof(int));


   if(ptr == MAP_FAILED){
       printf("Mapping Failed\n");
       return 1;
   }


   for(int i=0; i<A; i++)
       ptr[i] = i*10;


   for(int i=0; i<A; i++)
       printf("[%d] ",ptr[i]);


   printf("\n");
   int b = munmap(ptr, 10*sizeof(int));
   if(b != 0){
       printf("Unmapping Failed\n");
       return 1;
   }


   return 0;
}


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>


enum {SEGMENT_SIZE = 1000};


const char *data = "Hello there!";


int main(int argc, char *argv[]) {


   int status;
   int segment_id;


   segment_id = shmget (IPC_PRIVATE, SEGMENT_SIZE);
   char *sh_mem = (char *) shmat(segment_id, NULL, 0);


   printf("Segment ID %d\n", segment_id);
   printf("Attached at %p\n", sh_mem);
   memmove(sh_mem, data, strlen(data)+1);
   printf("%s\n", sh_mem);


   shmdt(sh_mem);
   shmctl(segment_id, IPC_RMID, 0);
   exit(EXIT_SUCCESS);
}


#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 16
char* a = "hello, world 1";
char* b = "hello, world 2";
char* c = "hello, world 3";
 int main()
{
   char inbuf[MSGSIZE];
   int p[2], i;
    if (pipe(p) < 0)
       exit(1);
    write(p[1], a, MSGSIZE);
   write(p[1], b, MSGSIZE);
   write(p[1], c, MSGSIZE);
    for (i = 0; i < 3; i++) {
      
       read(p[0], inbuf, MSGSIZE);
       printf("% s\n", inbuf);
   }
   return 0;
}
