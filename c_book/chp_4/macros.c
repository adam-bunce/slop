#include <stdio.h>

#define paste(front, back) front ## back

int main() {
    int hello, there;
    char tmp[] = paste(hello, there);

    printf("%s", tmp);
}