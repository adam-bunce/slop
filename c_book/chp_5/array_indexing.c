#include <stdio.h>

int main() {

    int a[5] = {1, 2, 3, 4, 5};

    int *pa;

    pa = &a[0];
    printf("%d\n", *pa);
    printf("%d\n", *(pa + 1));
    printf("%d\n", *pa + 2);
    printf("%d\n", *pa + 3);
    printf("%d\n", *pa + 4);

    printf("\na is the EXACT same as pa\n");
    printf("%d\n", *a);
    printf("%d\n", *(a + 1));
    printf("%d\n", *a + 2);
    printf("%d\n", *a + 3);
    printf("%d\n", *a + 4);

    printf("\n");
    printf("%d\n", pa[0]);
    printf("%d\n", pa[1]);
    printf("%d\n", pa[2]);
    printf("%d\n", pa[3]);
    printf("%d\n", pa[4]);

}