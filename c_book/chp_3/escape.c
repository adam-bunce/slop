#include "stdio.h"
#include "string.h"

void escape(const char s[], char t[]);

/* assumes same length */
void escape(const char s[], char t[]) {
    int cur = 0;
    int copy = 0;
    char c;

    while (( c= s[cur]) != '\0') {
        switch (c) {
            case '\t':
                t[copy] = '\\';
                t[copy+1] = 't';
                copy += 2;
                break;
            case '\n':
                // printf("\\t or \\n");
                t[copy] = '\\';
                t[copy+1] = 'n';
                copy += 2;
                break;
            default:
                // printf("%c", c);
                t[copy] = c;
                copy += 1;
                break;
        }
        cur++;
    }

    t[copy] = '\0';
}


int main() {
    char src[] = "h\tello\n";
    char dest[15];
    escape(src, dest);
    printf("%s\n", src);
    printf("%s\n", dest);
}