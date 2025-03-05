// page 22
# include <stdio.h>

int array_modification_test(int arr[]);

int main() {
    int c, i, nwhite, nother;
    int ndigit[10];

    printf("arrays.c\n\n");

    nwhite = nother = 0;

    for (i = 0; i<10; i++){
        ndigit[i] = 0;
    }

    /* no curly braces is crazy */
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ndigit[c-'0']++;
        else if (c == ' ' || c == '\n' || c == '\t')
            nwhite++;
        else
            nother++;

    printf("digits =");
    for (i = 0; i < 10; i ++)
        printf(" %d->%d",i, ndigit[i]);

    printf(", whitespaces = %d, other = %d\n", nwhite, nother);

    int arr1[5] = {1, 2, 3,4,5};
    array_modification_test(arr1);

    for (i = 0; i < 5; i++) {
       printf(" %d", arr1[i]);
    }
}


/* Arrays are passed as reference so if we modify it in a function we modify the original too*/
int array_modification_test(int arr[]) {
    arr[0] = 50;

    return 0;
}
