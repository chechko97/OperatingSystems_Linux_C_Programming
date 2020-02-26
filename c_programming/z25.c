#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   if(argc == 1) {
      exit(0);
   }
   int fd = open("serror.txt", O_RDWR | O_CREAT, 0666);
   if(fd == -1) {
      fprintf(stderr, "Error with file.");
      exit(-1);
   }
   close(2);
   dup(fd);
   
   if(execvp("sort", argv) == -1) {
      fprintf(stderr, "Error execing.");
      exit(-1);
   }
   exit(0);
}
