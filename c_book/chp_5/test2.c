#include <stdio.h>


void mstrcpy(char *src, char *dest) {
    int i = 0;

    // assign src[i] to dest[i] until src[i] == '\0'
    while ((dest[i] = src[i]) != '\0') {
        i++;
    }
}

void mpstrcpy(char *src, char *dest) {

}

int main() {
    char *pname = "something";
    char aname[] = "not";

    // same address, pointer copied not value.
    printf("%p\n", pname);
    printf("%p\n", aname);

    char dest[100]; // = "";
    mstrcpy(pname, dest);

    printf("runs\n");
    printf("%s\n", dest);
}