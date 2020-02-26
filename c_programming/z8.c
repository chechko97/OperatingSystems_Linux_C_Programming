#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
   int fd1 = open("/etc/passwd", O_RDONLY);
   int fd2 = open("./my_passwd", O_CREAT | O_RDWR | O_TRUNC, 0666);
   char c;
   while(read(fd1, &c, 1)) {
      if(c == ':') {
         write(fd2, "?", 1);
      }
      else {
         write(fd2, &c, 1);	 
      }   
   } 
   close(fd1);
   close(fd2);
   exit(0);
}
