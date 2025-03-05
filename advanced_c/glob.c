#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <fnmatch.h>
#include <stdlib.h>


// function runs if glob encounters an error
int errfunc(const char *epath, int eerrno) {
    printf("Error for: %s: %s", epath, strerror(eerrno));
    return 0;
}

int main() {
    glob_t pglob;
    // match ___r.c
    int result = glob("*r.c", GLOB_MARK | GLOB_ERR | GLOB_NOCHECK | GLOB_NOESCAPE | GLOB_NOSORT, NULL, &pglob);
    // match ____s.c (glob_append)
    glob("", GLOB_MARK | GLOB_ERR | GLOB_NOCHECK | GLOB_NOESCAPE | GLOB_NOSORT | GLOB_APPEND, errfunc,
         &pglob);

    // result = 0 if match
    // GLOB_NOMATCH no match
    // GLOB_ABORT erro on filed
    // GLOB_NOSPACE malloc faile

    for (size_t i = 0; i < pglob.gl_pathc; i++)
        printf("%2zu: %s\n", i, pglob.gl_pathv[i]);
    globfree(&pglob);

    return EXIT_SUCCESS;
}