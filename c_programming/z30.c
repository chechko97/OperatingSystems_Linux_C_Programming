#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
   char buf[32];
   int n = 0;
   while(1) {
      write(1, "stefcho@chechko97:~$ ", 21);
      n = read(0, &buf, sizeof(buf));
      n--;
      buf[n] = '\0';
      if(n < 1) {
         continue;
      } 
      if(strcmp(buf, "exit") == 0) {
         exit(0); 
      } 
      int pid = fork();  
      if(pid > 0) {
         wait(NULL);
      }
      else if(pid == 0) {
         if(execlp(buf, buf, (char*) NULL) == -1) {
            printf("%s: command not found\n", buf);
            exit(0);
         }
      }
      else {
         fprintf(stderr, "Could not fork.");
         exit(-1); 
      }  
   } 
}
