/* anything that starts with a # is the pre processor
 * #include
 * #define
 * 1. preprocessor runs, compile c code to machine code, link multiple files together
 * preprocessor is its own language
 * */

#include <stdio.h>


#define FOO 2
// because this literally replaces every instance of this with the exact text
// the PRECEDENCE of it is im porta
#define ADD(x, y) x + y

// brackets maintain precedence
#define BETTER_ADD(x, y) (x + y)


#define MUL(x, y) (x * y)
#define BETTER_MUL(x, y) ((x) * (y))


// multi range macro
// do while creates a new scope so things being redeclared arent cancer
#define SUM_RANGE(start, end)  {\
    int sum = 0;              \
    for (int x = (start); x < (end); x++) \
        sum += x;              \
    printf("sum: %d\n", sum);     \
    }

int main(void) {
    // we decalre sum here, but what if we a
    SUM_RANGE(1, 5); // redefine sum here, we need to create an extra scope

    // fine
    int x = ADD(2, 3);
    printf("%d\n", x);

    // not
    int y = 5 * ADD(2, 3); // 5 * 2 + 3 = 13, not 25 like we expect
    printf("%d\n", y);

    int z = 5 * BETTER_ADD(2, 3); // 5 * 2 + 3 = 13, not 25 like we expect
    printf("%d\n", z);


    int a = 5 * MUL(2, 3 + 2);
    // GOT: 5 * (2 * 3 + 2)
    // WANTED: 5 * (2 * (3 + 2))
    printf("%d\n", a);

    int b = 5 * BETTER_MUL(2, 3 + 2);
    // GOT: 5 * (2 * (3 + 2))
    printf("%d\n", b);


    return 0;
}