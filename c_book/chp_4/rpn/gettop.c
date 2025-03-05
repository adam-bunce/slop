#include "stdio.h"
#include "ctype.h"
#include "calc.h"

int mget_op(char s[]) {
    int i, c;
    while ((s[0] = c = mget_ch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c; // not a number
    i = 0;
    if (c == '-' || isdigit(c)) // collect integer part along with '-'
        while (isdigit(s[++i] = c = mget_ch()));
    if (c == '.') // collect fraction part
        while (isdigit(s[++i] = c = mget_ch()));
    s[i] = '\0';
    if (c != EOF)
        munget_ch(c);
//    if (strcmp(s, "-") == 0)
//        return '-';
    return NUMBER;
}
