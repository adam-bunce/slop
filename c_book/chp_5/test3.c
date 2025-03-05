#include <stdio.h>

int main() {
    // was unsure what the difference between these two was
    char a[] = "hello";
    char *b = "hello";

    a[3] = 'n';
    // b[3] = 'n';

    printf("%s\n", a);
    printf("%s\n", b);

}