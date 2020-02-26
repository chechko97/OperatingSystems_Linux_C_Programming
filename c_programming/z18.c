#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   if(argc != 2) {
      fprintf(stderr, "Wrong input!\n");
      exit(-1);
   }
   int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
   if(fd == -1) {
      fprintf(stderr, "Error writing in the file!");
   }
   int pid = fork();
   if(pid > 0) {
      wait(NULL);
      write(fd, "123\n", 4);   
   }
   else if(pid == 0) {
      write(fd, "abcd\n", 5);
      exit(0);
   }
   else {
      fprintf(stderr, "Error piping!");
      exit(-1);
  }

   exit(0);
}
