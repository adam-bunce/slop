#include <stdio.h>

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free pos

/* return pointer ot n characters */
char *alloc(int n) {
    // does it fit (10000 + 500 - 10 >= n)
    // 0 + 10_000 - 1_000 >= 50
    // 9_0000 >= 50 true, have room
    printf("have: %ld room", allocbuf + ALLOCSIZE - allocp);
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n; // old p
    } else {
        // oom
        return 0;
    }
}

void afree(char *p) {
    // pointer falls between min/max range of buffer, then we can free to that point
    if (p >= allocbuf & p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}