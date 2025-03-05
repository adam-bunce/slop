#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <search.h>

#define ARR_LEN(arr) (sizeof (arr) / sizeof (arr)[0])


int compar_str(const void *v1, const void *v2) {
    char *s1 = *(char **) v1;
    char *s2 = *(char **) v2;

    return strcmp(s1, s2);
}

int compar_int(const void *v1, const void *v2) {
    int i1 = *(int *) v1;
    int i2 = *(int *) v2;

    return i1 > i2;
}


int main(void) {
    char *strings[] = {"hello", "bonjour", "ola", "hallo", "bom dia"};
    int xs[] = {1, 5, 2, 8, 7};

    for (int i = 0; i < ARR_LEN(strings); i++) {
        printf("%s\n", strings[i]);
    }

    qsort(strings, ARR_LEN(strings), sizeof strings[0], compar_str);

    printf("------\n");
    for (int i = 0; i < ARR_LEN(strings); i++) {
        printf("%s\n", strings[i]);
    }
    printf("------\n");

    for (int i = 0; i < ARR_LEN(xs); i++) {
        printf("%d\n", xs[i]);
    }
    qsort(xs, ARR_LEN(xs), sizeof xs[0], compar_int);

    printf("------\n");
    for (int i = 0; i < ARR_LEN(xs); i++) {
        printf("%d\n", xs[i]);
    }


    // search xs b search
    int search_val = 1;
    int *svp = bsearch(&search_val, xs, ARR_LEN(xs), sizeof xs[0], compar_int);
    if (svp != NULL)
        printf("found value %p, %d\n", svp, *svp);
    else
        printf("not in there\n");


    int needle = 7;
    size_t len = ARR_LEN(xs);
    void *result = lfind(&needle, xs, &len, sizeof xs[0], compar_int);
    if (svp != NULL)
        printf("found value %p, %d\n", result, *(int *) result);
    else
        printf("not in there\n");


    return 0;
}