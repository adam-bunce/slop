#include <string.h>

void truncate(char *string, int max_len) {
    if (strlen(string) > max_len) {
        string[max_len - 3] = '.';
        string[max_len - 2] = '.';
        string[max_len - 1] = '.';
        string[max_len] = '\0';
    }
}
