#include <stdio.h>
#define ML 1000


int max;
char line[ML];
char longest[ML];


int get_line(void);
void my_copy(void);


/* print longest input line */
int main() {
    int len;

    extern int max;
    extern char longest[];

    max = 0;

    while ((len = get_line()) > 0) {
        if (len > max) {
            max = len;
            my_copy();
        }
    }

    /* there was a line */
    if (max > 0) {
        printf("%s", longest);
    }

    return 0;
}

/* get_line: read a line into s, return length */
int get_line(void) {
    int c, i;

    extern char line[];

    for (i = 0; i < ML -1 && (c=getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        i++;
    }

    // \0 is the null terminator
    line[i] = '\0';
    return i;
}

/** copy: copy 'from' into 'to'; assumes to is big enough */
void my_copy(void) {
   int i = 0;

   extern char line[], longest[];

   while ((longest[i] = line[i]) != '\0') {
       // printf("comp: %d\n", (to[i] == from[i]));
       i++;
   }
}