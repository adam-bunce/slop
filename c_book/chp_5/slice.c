#include <stdio.h>


void print_slice(int start, int stop, const int *array) {
    /* you cant return arrays form functions, so we are just going to print it*/
    if (stop < start) return;

    const int *start_ptr = array + start;

    int i = 0;
    while (i < stop - start) {
        // printf("i=%d\n", i);
        printf("%d \n", start_ptr[i]);
        i++;
    }
}

int main() {
    // 0 -> 4
    int a[5] = {1, 2, 3, 4, 5};

    print_slice(0, 2, a);
}