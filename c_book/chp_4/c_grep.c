#include "stdio.h"

#define MAXLINE 1000

int my_getline(char[], int);

int my_strindex(char[], char[]);

char pattern[] = "ould";

int main() {
    char line[MAXLINE];
    int found = 0;
    int pos = -1;

    while (my_getline(line, MAXLINE) > 0) {
        if ((pos = my_strindex(line, pattern)) >= 0) {
            printf("%s at index %d", line, pos); // last occurance
            found++;
        }
    }

    return found;
}


/* my_getline:  get line into s, return length */
int my_getline(char s[], int lim) {
    int c, i;

    i = 0;
    // DOES -- prefix/postfix matter here?
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int my_strindex(char s[], char t[]) {
    int i, j, k;

    // iterate through string
    for (i = 0; s[i] != '\0'; i++) {
        // from current position (j) (search str)
        // from current position (k) (string to search)
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {

        }
        // its a match if we moved, and reached the end of the search string
        if (k > 0 && t[k] == '\0') {
            return k - 1;
        }
    }

    return -1;
}


