#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char* argv[]) {
   if(argc != 3) {
      write(2, "Not the right number of arguments.\n", 35);
      exit(-1);
   }
   int fd1, fd2;
   char c;
   if((fd1 = open(argv[1], O_RDONLY)) == -1) {
      write(2, "File1 failed to open in read mode.\n", 35);
      exit(-1);
   }
   if((fd2 = open(argv[2], O_CREAT | O_WRONLY)) == -1) {
      write(2, "File2 failed to open in write mode.\n", 36);
      close(fd1);
      exit(-1);
   }
   while(read(fd1, &c, 1)) {
      write(fd2, &c, 1); 
   }
   close(fd1);
   close(fd2);
   exit(0);
}
