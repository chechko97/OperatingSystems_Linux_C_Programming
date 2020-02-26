#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   if(argc != 3) {
      fprintf(stderr, "Not the right number of arguments.\n");
      exit(-1);
   }
   int flag=0;
   if(strcmp(argv[1], "--min") == 0)
     flag=1;
   else if(strcmp(argv[1], "--max") == 0)
      flag=2;
   else if(strcmp(argv[1], "--print") == 0)
      flag=3;
   if(flag == 0) {
      fprintf(stderr, "Error!\n");
      exit(1);
   }

   int fd1;
   fd1 = open(argv[2], O_RDONLY);
   if(fd1 == -1) {
      fprintf(stderr, "Error while reading a file!\n");
      exit(1);
   }
   char buf[2];
   int num;
   if(flag == 1) {
      int min=999999;
      while((num = read(fd1, &buf, 2)) > 0) {
         int help = ((((uint16_t)buf[0]) << 8) | (0x00ff & buf[1]));
         if(help < min) {
	    min=help;  
         }
      }
      printf("%d\n", min); 
      close(fd1);
      exit(0);
   }
   if(flag == 2) {
      int max=0;
      while((num = read(fd1, &buf, 2)) > 0) {
         int help = ((((uint16_t)buf[0]) << 8) | (0x00ff & buf[1]));
         if(help > max) {
            max=help;
         }
      }
      printf("%d\n", max);
      close(fd1);
      exit(0);
   }
   if(flag == 3) {
      while((num = read(fd1, &buf, 2)) > 0) {
         printf("%d\n", (((uint16_t)buf[0]) << 8) | (0x00ff & buf[1]));
      }
      close(fd1);
      exit(0); 
   }
   close(fd1);
   exit(0);
}
