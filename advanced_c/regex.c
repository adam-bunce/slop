#include <regex.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


void group_regex(void) {
    regex_t preg;
    assert(regcomp(&preg, "(ab*)(cd*)", REG_EXTENDED) == 0);

    const size_t nmatch = 10;
    regmatch_t pmatch[nmatch + 1]; // matches, (first/last)
    char *s = "abbcddddd";

    int result = regexec(&preg, s, nmatch, pmatch, 0);
    if (result == 0) {
        printf("match\n");
        for (size_t i = 0; pmatch[i].rm_so != -1 && i < nmatch; i++) {
            char buf[256] = {0};
            strncpy(buf, s + pmatch[i].rm_so, pmatch[i].rm_eo - pmatch[i].rm_so);
            printf("start %lld, end %lld, %s\n", pmatch[i].rm_so, pmatch[i].rm_eo, buf);
        }
    } else if (result == REG_NOMATCH) {
        printf("no match\n");
    }

    regfree(&preg);

    return;
}


int main(void) {
    group_regex();
    return 1;


    regex_t preg;
    assert(regcomp(&preg, "^(ab)+", REG_ICASE | REG_EXTENDED) == 0); // does compile

    int result = regexec(&preg, "AB", 0, NULL, 0);
    if (result == 0)
        printf("match\n");
    else if (result == REG_NOMATCH)
        printf("no match\n");

    regfree(&preg);

    return 0;
}