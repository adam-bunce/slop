#include <stdio.h>


int main() {
   long bc;
   bc = 0;
   int c; /* we store chars in int because we need -1 to be valid for EOF or smth*/

   while ((c = getchar()) != EOF) {
       if (c == ' '  ||
           c == '\n' ||
           c == '\t' ) {
            bc++;
       }
   }

   printf("%ld", bc);
}