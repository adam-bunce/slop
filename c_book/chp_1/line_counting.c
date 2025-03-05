#include <stdio.h>

int main() {
    int c, nl;

    nl = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            nl++;
        }
    }

    /* here sometimes i get a # followed by D*/
    printf("%d\n", nl);
}