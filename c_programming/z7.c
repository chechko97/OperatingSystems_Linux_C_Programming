#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   int i=1;
   while(argv[i] != 0) {
      int fd1 = open(argv[i], O_RDONLY);
      if(fd1 == -1) {
        fprintf(stderr, "File %s failed to open in read mode.\n", argv[i]);
        exit(-1);
      }
      close(fd1);
      i++;
   }
   i=1;
   while(argv[i] != 0) { 
      int fd1 = open(argv[i], O_RDONLY);
      char c;
      while(read(fd1, &c, 1)) {
         write(1, &c, 1);
      }
      close(fd1);
      i++;
   }
   exit(0);
}
