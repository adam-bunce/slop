#include <limits.h>
#include <float.h>
#include <stdio.h>


int my_strlen(const char s[]);

int main() {
    printf("%f\n", FLT_MAX);
    printf("%d\n", UCHAR_MAX);
    printf("%d\n", UCHAR_MAX);
    printf("%d\n", '0');

    // erhm these do nothing
    printf("\007 \n");
    printf("\a\n");
    printf("hello\fworld\n");
    // vertical tab
    printf("hello\vworld\n");
    char tes[] = "adam is" "so cool" "wow" "this is one"
                                           "string"
                                           "isnt it";

    printf("%s\n", tes);
    printf("%d\n", my_strlen(tes));
    printf("hello \v \v world\n");

    enum codes {
        FOUR_HUNDRED = 400,
        FIVE_HUNDRED = 500,
        SIX_HUNDRED = 600
    };

    printf("%d\n", FIVE_HUNDRED);
}

int my_strlen(const char s[]) {
   int i;
   i = 0;

   while (s[i] != '\0') {
        // s[i] = 'G'; error here
       i++;
   }
   return i;
}