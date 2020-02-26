#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main() {
   if(execlp("date", "date", (char*)NULL) == -1) {
      err(10, "err execling");
   } else {
        printf("foobar\n");
   }

   exit(0);
}
