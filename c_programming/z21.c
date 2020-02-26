#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main (int argc, char* argv[]) {
   int f = open("serror.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
   dup2(f, 2);
   if (execvp("sort", argv) == -1) {
      err(1, "exec sort");
   }
}
