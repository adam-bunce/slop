#include "stdio.h"

#define BUF_SIZE 100
char buf[BUF_SIZE]; // buffer for unget_ch
int bufp = 0;       // next free position in buf

int mget_ch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void munget_ch(int c) {
    if (bufp >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
