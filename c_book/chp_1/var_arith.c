#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for farh = 0, 20, ... 300 */
int main() {

    int fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* lower limit of the table */
    upper = 300; /* upper limit of the table*/
    step = 20;   /* step size */

    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr-32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}