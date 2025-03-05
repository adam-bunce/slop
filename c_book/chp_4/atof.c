#include "ctype.h"
#include "stdio.h"

double atof(char s[]) {
    double val, power;

    int i, sign;

    for (i = 0; isspace(s[i]); i++); // skip whitespace

    sign = (s[i] == '-') ? -1 : 1;

    // if sign, then move to numbers b/c we consumed sign already
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    // left side of decimal
    val = 0.0;
    for (; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    // decimal
    if (s[i] == '.') {
        i++;
    }

    power = 1.0;
    for (; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'E' || s[i] == 'e') i++;

    int e_sign;
    e_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++;

    // only supports 1 digit #'s for E_
    if (isdigit(s[i])) {
        for (int m = s[i] - '0'; m > 0; m--) {
            switch (e_sign) {
                case -1:
                    power *= 10;
                    break;
                case 1:
                    power /= 10;
                    break;
                default:
                    printf("weird value in e_sign\n");
                    break;
            }
        }
    }

    // printf("sign:%d val:%f power:%f \n", sign, val, power);
    return sign * val / power;
}


int main() {
    printf("%f\n", atof("12.3e-3"));
    printf("%f\n", atof("12.3e2"));
    printf("%f\n", atof("12.3"));
}