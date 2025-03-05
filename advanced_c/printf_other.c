#include <stdlib.h>
#include <stdio.h>

int main(void) {

    FILE *f = fopen("foo", "w");
    fprintf(f, "%d, %d\n", 3, 2);
    fclose(f);


    // int fd = open():
    char buf[256] = {0};
    sprintf(buf, "%d, %d", 3, 2);
    printf("#%s#\n", buf);

    // int fd = open():
    char buf2[10] = {0};
    snprintf(buf2, 10, "%d, %d, %s", 3, 2, "user input string herre maybe its logn");

    // below breaks beacuse it wil overflow the buffer
    sprintf(buf2, "%d, %d, %s", 3, 2, "user input string herre maybe its logn");
    printf("#%s#\n", buf2);
    return 0;
}