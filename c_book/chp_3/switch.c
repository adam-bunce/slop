#include "stdio.h"
#include "stdlib.h"


#define SIZE 10

int main() {

    int c, i, nwhite, nother, ndigits[SIZE];
    nwhite = nother = 0;

    // init aray
    for (i = 0; i < SIZE; i++) ndigits[i] = 0;

    /* MACOS C^D is EOF signalp*/
    while ((c = getchar()) != EOF) {
        switch (c) {
            // you have to manually break, otherwise we fall through
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ndigits[c - '0']++;
                break;
            case ' ':
            case '\t':
            case '\n':
                nwhite++;
                break;
            default:
                nother++;
                // we add the break here as defensive programmign
                break;
            case 'p':
                break;
        }
    }

    printf("digits = ");
    for (i = 0; i < SIZE; i++)
        printf(" %d", ndigits[i]);

    printf(", white space = %d, other = %d\n", nwhite, nother);
    return EXIT_SUCCESS;
}