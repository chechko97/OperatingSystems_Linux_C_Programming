#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//$ cat /etc/passwd | cut -d ':' -f7 | uniq -c | sort -n
int main() {
   int pd1[2];
   if(pipe(pd1) == -1) {
      fprintf(stderr, "Could not pipe.\n");
      exit(-1);
   }
   int pid1 = fork();
   if(pid1 > 0) {
      close(pd1[1]);
      int pd2[2];
      if(pipe(pd2) == -1) {
         fprintf(stderr, "Could not pipe.\n");
         exit(-2);
      }
      int pid2 = fork();
      if(pid2 > 0) {
         close(pd2[1]);
         int pd3[2];
         if(pipe(pd3) == -1) {
            fprintf(stderr, "Could not pipe.\n");
            exit(-3);
         }
         int pid3 = fork();
         if(pid3 > 0) {
            close(pd3[1]);
            close(0);
            dup(pd3[0]);
            if(execlp("sort", "sort", "-n", (char*) NULL) == -1) {
               fprintf(stderr, "Could not exec.\n");
               exit(-4); 
            } 
         }
         else if(pid3 == 0) {
            close(pd3[0]);
            close(0);
            dup(pd2[0]);
            close(1);
            dup(pd3[1]);
            if(execlp("uniq", "uniq", "-c", (char*) NULL) == -1) {
               fprintf(stderr, "Could not exec.\n");
               exit(-3);
            } 
         } 
         else {
            fprintf(stderr, "Could not fork.\n");
            exit(-3); 
         }
      } 
      else if(pid2 == 0) {
          close(pd2[0]);
          close(0);
          dup(pd1[0]);
          close(1);
          dup(pd2[1]);
          if(execlp("cut", "cut", "-d", ":", "-f7", (char*) NULL) == -1) {
             fprintf(stderr, "Could not exec.\n");
             exit(-2);
          }
      } 
      else {
         fprintf(stderr, "Could not fork.\n");
         exit(-2);
      }
   }
   else if(pid1 == 0) {
      close(pd1[0]);
      close(1);
      dup(pd1[1]);
      if(execlp("cat", "cat", "/etc/passwd", (char*) NULL) == -1) {
         fprintf(stderr, "Could not exec.\n");
         exit(-1);
      } 
   }
   else {
      fprintf(stderr, "Could not fork.\n");
      exit(-1);
   }


   exit(0);
}
