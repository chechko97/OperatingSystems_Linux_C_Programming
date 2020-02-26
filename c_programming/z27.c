#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   if(argc < 2) {
      while(1) {
         char buf[32];
         int n = read(0, buf, 32);
         if(n < 1) {
            exit(0);
         }
         n--;
         buf[n] = '\0';
         if(strcmp("-", buf) == 0) {
            while(1) {
               char buf2[32];
               int m = read(0, buf2, 32);
               if(m < 1) {
                  exit(0);
               }
	       m--;
	       buf2[m] = '\0';
               printf("%s\n", buf2);
            }
            continue;
         } 
         int fd = open(buf, O_RDONLY);
         if(fd == -1) {
           fprintf(stderr, "Error opening the file.\n");
           exit(-1);
         }
         char c;
         while(read(fd, &c, 1) > 0) {
            printf("%c", c);
         }  
      }
   }
   if(strcmp(argv[1], "-n") == 0) {
      if(argc < 3) {
         int printLine=1;
         while(1) {
            char buf[32];
            int n = read(0, buf, 32);
            if(n < 1) {
               break;
            } 
            n--;
            buf[n] = '\0';
            if(strcmp("-", buf) == 0) {
               while(1) {
                  char buf2[32];
                  int m = read(0, buf2, 32);
                  if(m < 1) {
                     break; 
                  } 
                  m--;
                  buf2[m] = '\0';
                  printf("%d. ", printLine);
                  printLine++;
                  for(int j=0; j<m; j++) {
                     printf("%c", buf2[j]);
                     if(buf2[j] == '\n') {
                        printf("%d. ", printLine);
                        printLine++;
                     }
                  }
                  printf("\n");
               }
               continue; 
            }
            int fd = open(buf, O_RDONLY);
            if(fd == -1) {
              fprintf(stderr, "Error opening the file.\n");
              exit(-1);
            }
            char v;
            int lines=0;
            while(read(fd, &v, 1) > 0) {
               if(v == '\n') {
                  lines++;
               }
            }
            lseek(fd, 0, SEEK_SET);
            char c;
            int br=1;
            if(lines != 0) {
               printf("%d. ", printLine);
            }
            while(read(fd, &c, 1) > 0) {
               printf("%c", c);
               if(c == '\n') {
                  br++;
                  printLine++;
                  if(br <= lines) {
                     printf("%d. ", printLine);
                  }
               }
            }
         }
      }
      int printLine=1;
      for(int i=2; i < argc; i++) {
         if(strcmp("-", argv[i]) == 0) {
            while(1) {
               char buf2[32];
               int m = read(0, buf2, 32);
               if(m < 1) {
                  break;
               }
	       m--;
	       buf2[m] = '\0';
               printf("%d. ", printLine);
               printLine++;
               for(int j=0; j<m; j++) {
                  printf("%c", buf2[j]);
                  if(buf2[j] == '\n') {
                     printf("%d. ", printLine);
                     printLine++;
                  }
               }
               printf("\n");
            }
            continue;
         }
         int fd = open(argv[i], O_RDONLY);
         if(fd == -1) {
           fprintf(stderr, "Error opening the file.\n");
           exit(-1);
         }
         char v;
         int lines=0;
         while(read(fd, &v, 1) > 0) {
            if(v == '\n') {
               lines++;
            }
         }
         lseek(fd, 0, SEEK_SET); 
         char c;
         int br=1;
         if(lines != 0) {
            printf("%d. ", printLine);
         }  
         while(read(fd, &c, 1) > 0) {
            printf("%c", c);
            if(c == '\n') {
               printLine++;
               br++; 
               if(br <= lines) {
                  printf("%d. ", printLine);
               }
            }
         } 
      }
   }
   else {
      for(int i=1; i < argc; i++) {
         if(strcmp("-", argv[i]) == 0) {
            while(1) {
               char buf[32];
               int n = read(0, buf, 32);
               if(n < 1) {
                  break;
               }  
               n--;
               buf[n] = '\0';
               printf("%s\n", buf);
            }
            continue;  
         }
         int fd = open(argv[i], O_RDONLY);
         if(fd == -1) {
           fprintf(stderr, "Error opening the file.\n");
           exit(-1);
         }
         char c;
         while(read(fd, &c, 1) > 0) {
            printf("%c", c);
         }
      }
   }
  

   exit(0);
}
