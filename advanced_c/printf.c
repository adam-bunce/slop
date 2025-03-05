#include <stdio.h>

int main(void) {

    int a = 1;

    printf("double    %d\n", 32); // double
    printf("unsigned  %u\n", -32); //uint
    printf("float     %f\n", 32.32); // float
    printf("pointer   %p\n", &a);
    printf("character %c\n", 'a');
    printf("string    %s\n", "hello");
    printf("percent   %%\n");
    printf("expntl    %e\n", 123412321213.12321312);
    printf("exp/nml   %g\n", 123412321213.12321312);
    printf("exp/nml   %g\n", 123.12321312);

    printf("\n");
    printf("###%+-10d###\n", 32); // double
    printf("unsigned  %u\n", -32); //uint
    printf("float     %.2f\n", 32.323233); // float
    printf("pointer   %p\n", &a);
    printf("character %c\n", 'a');
    printf("string    %s\n", "hello");
    printf("percent   %%\n");
    printf("expntl    %e\n", 123412321213.12321312);
    printf("exp/nml   %g\n", 123412321213.12321312);
    printf("exp/nml   %g\n", 123.12321312);

    // substitute 10 for * here ,pad until we get 10, pad with 0's
    printf("%0*d\n", 10, -32);

    // suppsed to be human readable, but isnt :tears:
    printf("%'.2f\n", 1234567.89);

    long int l = 1351541354353154351;

    // overflowed?
    printf("%d\n", l);
    // didnt overflow
    printf("%ld\n", l);

    size_t size = 123412;
    printf("%zu\n", size);

    return 0;
}