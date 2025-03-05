#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void) {
    char s[] = "1,2,3,4,5";

    char *token = strtok(s, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "");
    }

    // also strsep

    return 0;
}