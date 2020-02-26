#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main(int argc, char* argv[]) {
   if(argc != 2) {
      fprintf(stderr, "err\n");
      exit(98);
   }
   if(execlp("ls", "ls", "-lrt", argv[1], (char*)NULL) == -1) {
      err(99, "err execling");
   }
   else {
      printf("foobar\n");
   }

   exit(0);
}
