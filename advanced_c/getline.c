#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc/malloc.h>


int main(void) {
    FILE *file = fopen("foo", "r");
    assert(file != NULL);

    // char *line = NULL;
    char *line = malloc(sizeof(char) * 2048);
    assert(line != NULL);
    size_t line_buffer_len;
    ssize_t read_size = 0;

    while ((read_size = getline(&line, &line_buffer_len, file)) != -1) {
        // remove new line
        line[read_size - 1] = '\0';
        printf("line = %s, malloc size=%zu\n", line, malloc_size(line));
    }
    // getline updates buffer w/ malloc
    // assumed the buffer was malloced initially
    free(line);

    assert(feof(file));


    fclose(file);
    return 0;
}


