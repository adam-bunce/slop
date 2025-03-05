#include <stdio.h>


float convert(float);

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0; /* lower limit of temp table*/
    upper = 300; /* upper limit */
    step = 20; /* step size */

    fahr = (float)lower;

    printf("FarH Celsius\n");
    while (fahr <= (float)upper) {
        celsius = convert(fahr);
        printf("%3.0f %9.1f\n", fahr, celsius);
        fahr = fahr + (float)step;
    }
}

float convert(float fahr) {
    return (float)(5.0/9.0) * (float)(fahr-32.0);
}