#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   int fd1;
   char c;
   int lines=0, words=0, chars=0;
   if(argc != 2) {
     fprintf(stderr, "error\n");
     exit(1); 
   }
   if((fd1 = open(argv[1], O_RDONLY)) == -1) {
     fprintf(stderr, "File failed to open in read mode!\n");
     exit(1);
   }
   while(read(fd1, &c, 1)) {
      if(c == '\n') {
         lines++;
         words++;  
      }
      else if(c == ' ') {
         words++; 
      }
      chars++;  
   }
   printf("File %s has:\n%d number of lines.\n%d number of words.\n%d number of chars.\n", argv[1], lines, words, chars);
   close(fd1);
   exit(0);
}
