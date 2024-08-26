#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define ARRAY_LEN(arr)     (sizeof (arr) / sizeof(arr[0]))
#define FILE_NAME_MAX_LEN  15
#define DIR_FILE_SIZE      10

void is_loaded(void) {
    printf("loaded files.c or files.h");
}

int ls_in_dir(char *dir, char **dest_buf, size_t buf_size, __uint8_t dir_types) {
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    if ((folder = opendir(dir)) == NULL)
        return -1;

    while ((entry = readdir(folder)) && files < buf_size) {
        if (entry->d_type != dir_types) continue;

        truncate(entry->d_name, FILE_NAME_MAX_LEN);
        // TODO: is this sketchy?
        dest_buf[files] = entry->d_name;
        files += 1;
    }

    return files;
}


// get list of directories (str split?)
void ls_directiors_in_dir() {

}

// get file contents from name into buffer


int main() {
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        printf("failed to get cwd\n");


    // 5 files max?
    int files_buf_size = sizeof(char) * FILE_NAME_MAX_LEN * DIR_FILE_SIZE;
    char **files = malloc(files_buf_size);

    int count = ls_in_dir(cwd, files, files_buf_size, DT_REG);
    printf("count: %d", count);
    for (int i = 0; i < count; i++)
        printf("%d %s\n", i, files[i]);

    free(files);
}