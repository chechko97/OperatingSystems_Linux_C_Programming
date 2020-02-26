#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
   if(argc > 2) {
      fprintf(stderr, "Too many arguments.\n");
      exit(-1);
   }
   if(argc == 2) {
      if(strlen(argv[1]) > 4) {
         fprintf(stderr, "The parameter is more than 4 symbols.\n");
         exit(-2);
      }
   }
   if(argc == 1) {
      while(1) {
         char buf[64];
         int n = read(0, &buf, sizeof(buf));
         if(n < 1) {
            exit(0);
         }
         else if(n == 1) {
            continue;
         }
         int br=0;
         for(int i=0; i<=n; i++) {
            if(buf[i] == '\n' || buf[i] == ' ') {
               br=0;
            }
            else {
               br++;
               if(br > 4) {
                  fprintf(stderr, "More than 4 symbols.\n");
                  exit(-3);
               }
            }
         }
         n--;
         buf[n] = '\0';
         printf("%s\n", buf);   
      }           
   }
   else {
      while(1) {
         char buf[64];
         int n = read(0, &buf, sizeof(buf));
         if(n < 1) {
            break;
         }
         char buf1[4];
         char buf2[4];
         int flag=0; 
         int br=0, p=0;
         for(int i=0; i<n; i++) {
            if(buf[i] == '\n' || buf[i] == ' ') {
               if(flag == 0) {
                  buf1[br] = '\0';
                  p=br;  
                  flag = 1;
                  br=0;  
               }
               else {
                  buf2[br] = '\0';
                  flag = 0; 
                  int pid = fork();
                  if(pid > 0) {
                     wait(NULL);
                     for(int j=0; j<p; j++) {
                        buf1[j] = '\0';
                     }
                     for(int j=0; j<br; j++) {
                        buf2[j] = '\0';
                     }
                     br=0;  
                  }
                  else if(pid == 0) {
                     if(execlp(argv[1], argv[1], buf1, buf2, (char*) NULL) == -1) {
                        fprintf(stderr, "Could not exec.\n");
                        exit(-6);   
                     }
                  }
                  else {
                     fprintf(stderr, "Could not fork.");
                     exit(-5);   
                  }
               }  
            }
            else {
               if(flag == 0) {
                  buf1[br++] = buf[i];
                  if(br > 4) {
                     fprintf(stderr, "More than 4 symbols.\n");
                     exit(-4);  
                  }
                  if(i == n-2) {
                     buf1[br] = '\0';
                     if(execlp(argv[1], argv[1], buf1, (char*) NULL) == -1) {
                        fprintf(stderr, "Could not exec.\n");
                        exit(-6);
                     } 
                  }
               }
               else {
                  buf2[br++] = buf[i];
                  if(br > 4) {
                     fprintf(stderr, "More than 4 symbols.\n");
                     exit(-4);
                  }
                  //if(i == n-1) {
                    // buf2[br] = '\0';
                     //if(execlp(argv[1], argv[1], buf2, (char*) NULL) == -1) {
                      //  fprintf(stderr, "Could not exec.\n");
                       // exit(-6);
                     //}
                  //}
               }
            }
           
         }  
      }
   }


   exit(0);
}
