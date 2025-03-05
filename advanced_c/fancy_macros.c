#include <stdio.h>

// # stringifys the variable name input (or its value)
#define FOO(x, y) printf("%s + %s = %d\n", #x, #x, (x) + (y))


// Tokenize (wtf!) (not as alue but as token to dynamically create new var name?)

//
#define PREFIX(var_name) new_##var_name

#define GENERIC_ADD_FUNC(type) \
    type add_##type(type x, type y) { \
        return x + y;               \
    }

// add_int
GENERIC_ADD_FUNC(int)

// add_float
GENERIC_ADD_FUNC(float)

int main(void) {
    int first = 123;
    int second = 123;
    FOO(first, second);

    // dynamically gen variable name
    int PREFIX(foo) = 123;

    printf("%d\n", new_foo);

    printf("%f\n", add_float(2.5, 1.5));
    printf("%d\n", add_int(2, 1));


    return 0;
}