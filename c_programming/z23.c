#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   if(argc != 2) {
      fprintf(stderr, "Not the right number of arguments!\n");
      exit(-1); 
   }
   int fd = open(argv[1], O_RDONLY);
   if(fd == -1) {
     fprintf(stderr, "Error opening the file!\n"); 
     exit(-1); 
   }
   int pd[2];
   if(pipe(pd) == -1) {
      fprintf(stderr, "Error piping.\n");
      exit(-1);
   }
   int pid = fork();
   if(pid > 0) {
      close(pd[1]);
      close(0);
      dup(pd[0]);
      execlp("sort", "sort", (char*) NULL);
   }
   else if(pid == 0) {
      close(pd[0]);
      close(1); 
      dup(pd[1]);
      execlp("cat", "cat", argv[1], (char*) NULL); 
   }
   else {
      fprintf(stderr, "Error forking.\n");
      exit(-1);
   }
   exit(0);
}
