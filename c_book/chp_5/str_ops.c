#include <stdio.h>


void mstrcat(char *s, char *t) {
    // move s t end of itself
    while (*s != '\0') {
        s++;
    };

    while ((*s++ = *t++) != '\0');

}

int main() {
    char a[] = "hello";
    char b[] = " world";

    mstrcat(a, b);

    printf("'%s'\n", a);
}