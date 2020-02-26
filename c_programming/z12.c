#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

int main() {
   if(execlp("sleep", "sleep", "10", (char *)NULL) == -1) {
      err(99, "error execling");
      exit(1);
   }
   else {
      printf("foobar\n");
   }

   exit(0);
}
