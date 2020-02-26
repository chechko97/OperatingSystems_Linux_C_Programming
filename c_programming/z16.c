#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
   if(argc != 2) {
      fprintf(stderr, "Not the right arguments.");
      exit(-1); 
   }
   int pd[2];
   if(pipe(pd) == -1) {
      fprintf(stderr, "Can not pipe.");
      exit(-1);
   }
   int pid = fork();
   if(pid > 0) {
      close(pd[0]);
      write(pd[1], argv[1], strlen(argv[1]));
      close(pd[1]);
      wait(NULL);      
   }
   else if(pid == 0) {
      close(pd[1]);
      char c;
      while(read(pd[0], &c, 1) > 0) {
         write(1, &c, 1);
      }
      write(1,"\n", 1);
      close(pd[0]);   
   }
   else {
      fprintf(stderr, "Can not pipe.");
      exit(-1);
   }
   

   exit(0);
}
