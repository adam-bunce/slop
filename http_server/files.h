#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct file_info {
    char file_type[40]; // 40 should be enough right?
    char *file_content;
    long long int file_length;
};

int populate_file_struct(struct file_info *dest, char *file_path);

void file_ext_to_type(char *ext, char *dest_buf);

bool is_dir(char *path);