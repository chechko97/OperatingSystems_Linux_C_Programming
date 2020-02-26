#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   if(argc > 2) {
      fprintf(stderr, "Wrong input!\n");
      exit(-1);
   }
   else if(argc == 1) {
      while(1) {
         char buf[32];
         int n = read(0, buf, 32);
         if(n < 1) {
            break;
         }
         int br=0;
         for(int j=0; j<n; j++) {
            if(buf[j] == '\n' || buf[j] == ' ') {
               br=0;
            }
            else {
               br++;
            }
            if(br > 4) {
               fprintf(stderr, "More than 4 symbols.\n");
               exit(-1); 
            } 
         }  
         n--;
         buf[n] = '\0';
         printf("%s\n", buf);    
      }
   }
   else if(argc == 2){
      if(strlen(argv[1]) > 4) {
         fprintf(stderr, "Command is more than 4 symbols.\n");
         exit(-1); 
      }
      while(1) {
         char buf[32];
         int n = read(0, buf, 32);
         if(n < 1) {
            break;
         }
         n--;
         buf[n] = '\0';
         int br=0;   
         char buf2[5];
         char buf3[5];
         int flag=0;
         int l,p;
         for(int j=0; j<n; j++) { 
            if(buf[j] == '\n' || buf[j] == ' ') {
               if(flag == 0) {
                  flag=1;
                  buf2[br++] = '\0';
                  l=br;
               }
               else { 
                  flag=0;
                  buf3[br++] = '\0';
                  p=br;  
               }
               if(flag == 0) {     
                  int pid = fork();
                  if(pid > 0) {
                     wait(NULL);
                  }
                  else if(pid == 0) {
                     execlp(argv[1], argv[1], buf2, buf3, (char*) NULL); 
                  }
                  else {
                     fprintf(stderr, "Error forking.\n");
                     exit(-1);   
                  }  
                  for(int k=0; k<l; k++) {
                     buf2[k] = '\0';
                  }
                  for(int k=0; k<p; k++) {
                     buf3[k] = '\0';
                  }
               }
               br=0;
            } 
            else { 
               if(flag == 0) {
                  if(j == n-1) {
                     buf2[br++] = buf[j];
                     if(br > 4) {
                        fprintf(stderr, "More than 4 symbols.\n");
                        exit(-1);
                     }
                     buf2[br++] = '\0';
                     execlp(argv[1], argv[1], buf2, (char*) NULL); 
                  }
                  buf2[br++] = buf[j];
                  if(br > 4) {
                     fprintf(stderr, "More than 4 symbols.\n");
                     exit(-1);
                  }
               }
               else {
                  if(j == n-1) {
                     buf3[br++] = buf[j];
                     if(br > 4) {
                        fprintf(stderr, "More than 4 symbols.\n");
                        exit(-1);
                     }
                     buf3[br++] = '\0';
                     execlp(argv[1], argv[1], buf2, buf3, (char*) NULL);
                  }
                  buf3[br++] = buf[j];
                  if(br > 4) {
                     fprintf(stderr, "More than 4 symbols.\n");
                     exit(-1);
                  } 
               }
            }
         }
      }
   }

   exit(0);
}
