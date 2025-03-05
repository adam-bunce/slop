#include <stdio.h>

int main() {
    long nc;
    nc = 0;

    /* \n is being included as a character*/
    while (getchar() != EOF)
        nc++;

    printf("%ld\n", nc);
}