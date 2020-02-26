#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   char cmd[32];
   while(1) {
      write(1, "stefcho@chechko97:~$ ", 21);
      int n = read(0, cmd, 32);
      n--;
      cmd[n] = '\0'; 
      if(strcmp("exit", cmd) == 0) {
         exit(0);
      } 
      int pid = fork();
      if(pid > 0) {
         wait(NULL);    
      }
      else if(pid == 0) {   
         execlp(cmd, cmd, (char*) NULL);
      }
      else {
         fprintf(stderr, "Error forking.");
         exit(-1);   
      }
   }



   exit(0);
}
