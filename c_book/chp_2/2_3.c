#include <stdio.h>


int my_htoi(const char[]);

/* [] going on the actual thing is retarded ngl */
int my_htoi(const char hex[]) {

    int c;
    int res = 0;
    for (int i = 0; (c = hex[i]) != '\0'; i++){

        // shift last number right
        res *= 16;
        if (i == 0 && c == '0') {
            // remove 0x or 0X
            c = hex[i++];
        } else if (c >= '0' && c <= '9') {
            // c is digit
            res += c - '0';
        } else if (c >= 'a' && c <= 'f') {
            //  letter
            res += 10 + (c - 'a') ;
        } else if (c >= 'A' && c <= 'F') {
            //  uppercase letter
            res += 10 + (c - 'A') ;
        }
    }

    return res;
}

int main() {
    /*
     * write the function htoi(s) which converts a string of hex digits (include an optional (0x or 0X)
     * into its equivalent integer value, the allowable digits are 0->9, a-f and A through F
     */

     // f * 1
     // f * 16
     // f * 16 * 16
     // f * 16 * 16 * 16
     // ...
     // 15
    printf("%d\n",(16 * 15 ) + (1 * 15));
    char value[] = "0xff"; // this is null terminated \0
    int n = my_htoi(value);
    printf("%d\n", n);


    // binary: [8 4 2 0]
    // hex : [256 16 1]
    // [_ _ f 0 ]  = 16 * f(15) + 1 * 0 = 240
    // [_ _ f 0 ]  = 16 * f(15) + 1 * 0 = 240

    printf("%d\n", + (16 * 15) + (1 * 0));
    char value2[] = "0xf0"; // this is null terminated \0
    n = my_htoi(value2);
    printf("%d\n", n);

    printf("%d\n",(256 * 3) + (16 * 10) + (1 * 15));
    char value3[] = "0x3af"; // this is null terminated \0
    n = my_htoi(value3);
    printf("%d\n", n);

}