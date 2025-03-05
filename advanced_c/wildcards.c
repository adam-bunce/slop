#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <fnmatch.h>

void smth(void) {
    char *s = "path/to/file";
    // if you remove slashes it still matches, FNM_PATHNAME fixes this
    int result = fnmatch("path/*file", s, FNM_PATHNAME);
    if (result == 0)
        printf("match\n");
    else if (result == FNM_NOMATCH)
        printf("no match\n");

    char *s2 = "path/to/.file"; // hidden file
    // if you remove slashes it still matches, FNM_PATHNAME fixes this
    int result2 = fnmatch("path/*/.file", s2, FNM_PATHNAME | FNM_PERIOD);
    if (result2 == 0)
        printf("match\n");
    else if (result2 == FNM_NOMATCH)
        printf("no match\n");

}

int main(void) {
    smth();

    return 0;

    char *s = "hello world";
    // * matchs any #
    // ? matches 1
    // [a-z] is character range
    // [abc] is character class match a b or c
    // [:alpha:]  all lower alpha

    // flags:
    //  FNM_NOESCAPE doesnt escape things
    //
    int result = fnmatch("hel\\* world", s, FNM_NOESCAPE);
    if (result == 0)
        printf("match\n");
    else if (result == FNM_NOMATCH)
        printf("no match\n");
    else
        printf("uhh\n");

    return 0;
}