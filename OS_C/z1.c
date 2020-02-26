#include <stdio.h>
#include <stdlib.h>

int main() {
   int n;
   printf("Enter number: ");
   scanf("%d", &n);
   if(n >= 0) 
      printf("%d\n",n+2);
   else
      printf("Wrong input!\n");
   exit(0);
}
