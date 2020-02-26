#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
   int fd = open("gg.txt", O_WRONLY | O_CREAT, 0666);
   int fd_stdout = dup(1);
   close(1);
   dup(fd);
   write(1, "kolelo\n", 7);
   close(1);
   dup(fd_stdout);
   fprintf(stdout, "trotro\n");

   exit(0);
}
