#include <stdio.h>

struct Vec2 {
    int x;
    int y;
};

int scale_sum(int scalar, struct Vec2 v) {
    return scalar * v.x + scalar * v.y;
}

int sum(int xs[], int len) {
    int s = 0;
    for (int i = 0; i < len; i++)
        s += xs[i];
    return s;
}

int main(void) {
    struct Vec2 v;
    v.x = 2;
    v.y = 3;
    int result = scale_sum(4, v);
    printf("%d\n", result);


    // anon
    int anon_result = scale_sum(4, (struct Vec2) {2, 3});
    printf("%d\n", anon_result);


    int s = sum((int[5]) {1, 2, 3, 5, 6}, 5);
    printf("%d\n", s);

    struct Vec2 smth = {.x =  1, .y =  2};
    printf("%d\n", scale_sum(2, smth));


    return 0;
}