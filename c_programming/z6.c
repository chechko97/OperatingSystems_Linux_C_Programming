#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
   int fd1 = open(argv[1], O_RDWR); 
   int fd2 = open(argv[2], O_RDWR);
   int fd3;
   if(argc != 3) {
      fprintf(stderr, "Not the right number of arguments!\n");
      exit(-1);
   }
   if(fd1 == -1) {
     fprintf(stderr, "File failed to open in read mode!\n"); 
     exit(-1); 
   }
   if(fd2 == -1) {
     close(fd1); 
     fprintf(stderr, "File failed to open in read mode!\n");
     exit(-1);
   }
   if((fd3 = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC)) == -1) {
      close(fd1);
      close(fd2);
      fprintf(stderr, "err\n");  
      exit(-1); 
   }

   char c[4096];
   ssize_t read_size;
   while((read_size = read(fd1, &c, sizeof(c))) > 0) {
      if(write(fd3, &c, read_size) != read_size) {
        close(fd1);
        close(fd2);
        close(fd3);
	fprintf(stderr, "Error while writing!\n");
        exit(-1);
      }
   }
   lseek(fd1, 0, SEEK_SET);
   while((read_size = read(fd2, &c, sizeof(c))) > 0) {
      if(write(fd1, &c, read_size) != read_size) {
        close(fd1);
        close(fd2);
        close(fd3);
        fprintf(stderr, "Error while writing!\n");
        exit(-1);
      }
   }
   lseek(fd2, 0, SEEK_SET);
   lseek(fd3, 0, SEEK_SET);
   while((read_size = read(fd3, &c, sizeof(c))) > 0) {
      if(write(fd2, &c, read_size) != read_size) {
        close(fd1);
        close(fd2);
        close(fd3);
        fprintf(stderr, "Error while writing!\n");
        exit(-1);
      }
   }
   close(fd1);
   close(fd2);
   close(fd3);
   remove("temp.txt");
   exit(0);
}
