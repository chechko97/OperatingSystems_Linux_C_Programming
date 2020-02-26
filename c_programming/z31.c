#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   int fd = open("serror.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
   if(fd == -1) {
      fprintf(stderr, "Error with fd.\n");
      exit(-1);
   }
   close(2);
   dup(fd);
   if(execvp("sort", argv) == -1) {
      fprintf(stderr, "Could not exec.\n");
      exit(-3);
   }

   exit(0);
}
