#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "files.h"

#define ARRAY_LEN(arr)     (sizeof (arr) / sizeof(arr[0]))
#define FILE_NAME_MAX_LEN  15
#define DIR_FILE_SIZE      10


void file_ext_to_type(char *ext, char *dest_buf) {
    if (strcmp(ext, ".html") == 0) strcpy(dest_buf, "text/html");
    else if (strcmp(ext, ".png") == 0) strcpy(dest_buf, "image/png");
    else if (strcmp(ext, ".jpg") == 0) strcpy(dest_buf, "image/jpeg");
    else if (strcmp(ext, ".txt") == 0) strcpy(dest_buf, "text/plain");
    else
        strcpy(dest_buf, "application/octet-stream");

}

bool is_dir(char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

// NEED TO FREE  file_info.content
int populate_file_struct(struct file_info *dest, char *file_path) {
    // set size
    struct stat st;
    if (stat(file_path, &st) == -1) {
        dest->file_content = "404 not found";
        return EXIT_FAILURE;
    }
    dest->file_length = st.st_size;

    // rip out extension set type
    int pos = 0;
    while (file_path[pos] != '\0') {
        pos++;
    }

    // rewind to .
    while (file_path[pos] != '.') {
        pos--;
    }

    // read from .->end (extension)
    char *ext = malloc(sizeof(char) * 10);
    int i = 0;
    while (file_path[pos] != '\0') {
        ext[i++] = file_path[pos++];
    }

    file_ext_to_type(ext, dest->file_type);
    free(ext);

    // +1 for \0?
    dest->file_content = malloc(sizeof(char) * dest->file_length + 1); // NOTE: must free file content after use
    FILE *f = fopen(file_path, "rb");
    fread(dest->file_content, dest->file_length, 1, f);

    return EXIT_SUCCESS;
}