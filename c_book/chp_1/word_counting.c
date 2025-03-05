#include <stdio.h>

#define IN  1 /* inside of word */
#define OUT 0 /* outside of word */


int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        nc++; /* got a character */

        if (c == '\n') nl++; /* got a new line*/
        if (c == ' ' || c == '\n' || c == '\t') {
            /* finished word */
            state = OUT;
        }
        else if (state == OUT) {
            /* read a normal char, in word now */
           state = IN;
           nw++;
        }
    }

    printf("Lines Words Chars\n");
    printf("%5d %5d %5d\n", nl, nw, nc);
}