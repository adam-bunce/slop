#include <stdio.h>


void swp(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int ptr_str_len(const char *s) {
    // uses the fact that s is the address of the first element in the array
    const char *p = s;
    // p is going move until we get to the end of it

    while (*p != '\0') {
        p++;
    }

    // end - start = length right?
    return p - s;
}

int main() {
    int x = 3;
    int y = 12;
    int *ip;
    int *ip_2;
    ip_2 = &y;


    ip = &x;

    (*ip)++;

    // expect 4
    printf("%d\n", *ip);

    // garbage value, incremented actual address. not value at address.
    *ip++;
    printf("%d\n", *ip);

    // set it to the other pointer's address
    ip = ip_2;
    printf("%d\n", *ip);


    int a = 5;
    int b = 1;

    printf("a:%d b:%d\n", a, b);
    swp(&a, &b);
    printf("a:%d b:%d\n", a, b);


    // de
    int tmp = 0;
    // this isn't null? tf? what is dereferencing a null pointer then?
    int *tmpP = &tmp;
    printf("derefrence 0 ptr: %d\n", *tmpP);


    char word[] = "hello world";
    char *pword = "hello world";

    // don't need to dereference here cause that's just how strings work
    printf("length of %s is %d", word, ptr_str_len(word));
    printf("%s", pword);
}