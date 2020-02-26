#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//$cat /etc/passwd | cut -d ':' -f7 | uniq -c | sort -n
int main() {
   int pd1[2];
   if(pipe(pd1) == -1) {
      fprintf(stderr, "Error piping.");
      exit(-1);  
   }
   int pid1 = fork();
   if(pid1 > 0) {
      close(pd1[1]);
      int pd2[2];
      if(pipe(pd2) == -1) {
         fprintf(stderr, "Error piping.");
         exit(-1);
      }
      int pid2 = fork();
      if(pid2 > 0) {
         close(pd2[1]);
         int pd3[2];
         if(pipe(pd3) == -1) {
            fprintf(stderr, "Error piping.");
            exit(-1);
         }
         int pid3 = fork();
         if(pid3 > 0) {
            close(pd3[1]);
            close(0);
            dup(pd3[0]);
            execlp("sort", "sort", "-n", (char*) NULL);       
         }
         else if(pid3 == 0) {
            close(0);
            dup(pd2[0]);
            close(pd3[0]); 
            close(1);
            dup(pd3[1]);
            execlp("uniq", "uniq", "-c", (char*) NULL);  
         }
         else {
         fprintf(stderr, "Error forking.");
         exit(-1);
         } 
      }
      else if(pid2 == 0) {
         close(0);
         dup(pd1[0]);
         close(pd2[0]);
         close(1);
         dup(pd2[1]);
         execlp("cut", "cut", "-d", ":", "-f7", (char*) NULL);       
      }
      else {
         fprintf(stderr, "Error forking.");
         exit(-1);
      }  
   }
   else if(pid1 == 0) {
      close(pd1[0]);
      close(1);
      dup(pd1[1]);
      execlp("cat", "cat", "/etc/passwd", (char*) NULL); 
   }
   else {
      fprintf(stderr, "Error forking.");
      exit(-1);
   }



   exit(0);
}
