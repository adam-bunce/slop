#include <stdio.h>
#include <stdarg.h>


int sum_all(int count, ...) {
    // initalize variable argument list
    va_list ap; // arg pointer
    // va start
    va_start(ap, count);
    int sum = 0;

    for (int i = 0; i < count; i++) {
        int x = va_arg(ap, int);
        sum += x;
    }

    va_end(ap);
    return sum;
}


int main(void) {
    int out = sum_all(5, 1, 2, 3, 4, 5);

    printf("%d\n", out);

}