#include "stdio.h"
#include "stdbool.h"


void squeeze(char[], char[]);

bool is_in(char a[], char b) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == b) {
            return true;
        }
    }
    return false;
}

void squeeze(char a[], char b[]) {
    int copy_pos = 0;

    for (int view_pos = 0; a[view_pos] != '\0'; view_pos++) {
        if (is_in(b, a[view_pos])) {
            // shift normal, don't copy
            // view_pos += 1;
        } else {
            // copy and shift
            a[copy_pos++] = a[view_pos];

            /*
             * alternatively:
             * a[copy_pos] = a[view_pos];
             * copy_pos++;
             * */
        }
    }

    a[copy_pos] = '\0';

}

void other_squeeze(char s[], int c) {
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0';
}


int main() {

    char s[] = "hello";
    int c = 'l';

    printf("%c is in %s: %d\n", c, s, is_in(s, c));
    other_squeeze(s, c);
    printf("%s\n", s);


    char a[] = "abcdefg";
    char b[] = "bdf";
    squeeze(a, b);
    printf("ps: %s\n", a);


}