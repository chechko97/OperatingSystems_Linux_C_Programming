#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//ls -l | wc -l
//fds: 0-STDIN, 1 - STDOUT , 2 - STDERR
//pd[0] - input
//pd[1] - output

void main(int argc, char *argv[]) {
   int pd[2];
   if(pipe(pd) == -1) {
      fprintf(stderr, "Could not create pipe");
      exit(1);
   }
  
   int pid = fork();
   
   if (pid > 0) { // parent
      close(pd[1]);
      close(0);
      dup(pd[0]);
      execlp("wc", "wc", "-l", (char*) NULL);
   } else if (pid == 0) { // child
      close(pd[0]);
      close(1);
      dup(pd[1]);
      execlp("ls", "ls", "-l", (char*) NULL);
   } else {
    	fprintf(stderr, "Could not fork.");
    	exit(1);
   }

   exit(0);
}
