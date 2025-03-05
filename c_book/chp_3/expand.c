#include "stdlib.h"
#include "stdio.h"

// they probably use a trie under the hood for intellisense on named expressions
#define MAX_WORDS 3  // # of words
#define MAX_WORD_LEN 10 // word len

#define and &&

void expand(char[], char[]);

void expand(char src[], char dest[]) {
    int pos, copy;
    char c;
    char from, to;
    printf("%s\n", src);

    pos = 0;
    // eat leading dashes
    while ((c = src[pos]) == '-') pos++;
    from = src[pos++]; // grab pos, then increment it

    while ((c = src[pos]) != '\0') {
        printf("\n");
        // fresh
        while ((c = src[pos]) == '-') pos++;
        if (c <= 'z' and c >= 'a'
            || c <= '9' and c >= '0') {
            printf("case 1\n");
            // eat middle dashes
            to = src[pos++]; // grab pos, then increment it

            printf("from: %c\n", from);
            printf("to: %c\n", to);
        } else if (c == '-') {
            printf("case 2\n");
            from = to;
            pos++;
        } else {
            printf("unknown\n");
        }
    }
    printf("------------------------\n");

}

/* i skip this one :/ */

int main() {
    char inputs[MAX_WORDS][MAX_WORD_LEN] = {"a-b-c", "a-z0-9", "-a-z"};
    char dest[MAX_WORD_LEN];

    for (int i = 0; i < MAX_WORDS; i++) {
        expand(inputs[i], dest);
    }


    return EXIT_SUCCESS;
}