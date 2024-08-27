#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "files.h"
#include "http.h"

int build_http_response(char **dest_buf, struct file_info *file_info, enum Status status) {
    int size = 0;
    char *version;
    size += asprintf(&version, "HTTP/1.0 %d %s\r\n", status, http_resp_message_lookup[status]);

    char *headers;
    size += asprintf(&headers, "Content-Type: %s\r\n"
                               "Content-Length: %lld\r\n",
                     file_info->file_type,
                     file_info->file_length
    );

    size += asprintf(dest_buf, "%s%s\r\n%s\n\r\n", version, headers, file_info->file_content);

    free(headers);
    free(version);
    return size;
}

void parse_request(char *request_buf, struct request *dest) {
    // longest is options  + \0
    char method[8];
    int i;
    for (i = 0; request_buf[i] != ' '; i++) {
        method[i] = request_buf[i];
    }
    method[i] = '\0';

    if (strcmp(method, "GET") == 0) dest->method = GET;
    else if (strcmp(method, "POST") == 0) dest->method = POST;
    else if (strcmp(method, "PUT") == 0) dest->method = PUT;
    else if (strcmp(method, "DELETE") == 0) dest->method = DELETE;
    else if (strcmp(method, "OPTIONS") == 0) dest->method = OPTIONS;

    // eat space
    while (request_buf[i] == ' ') i++;

    char path[100];
    int j = 0;
    path[j++] = '.';
    while (request_buf[i] != ' ') {
        path[j++] = request_buf[i++];
    }
    path[j] = '\0';

    strcpy(dest->path, path);
}

void get_404_response(char **dest_buf) {
    char *version;
    asprintf(&version, "HTTP/1.0 %d %s\r\n", NOT_FOUND, http_resp_message_lookup[NOT_FOUND]);


    char *not_found_page = "404 not found";

    char *headers;
    asprintf(&headers, "Content-Type: %s\r\n"
                       "Content-Length: %lu\r\n",
             "text/plain",
             strlen(not_found_page) * sizeof(char)
    );

    // issue is dest_buf i think
    asprintf(dest_buf, "%s%s\r\n%s\n\r\n", version, headers, not_found_page);
    free(headers);
    free(version);
}

// assumes path is directory
void build_dir_response_body(char **dest_buf, char *path) {
    // NOTE: trace trap if too small
    char dirs[2048] = "";
    char files[2048] = "";
    char dest[2048 * 2] = "";
    strcat(dest, "<html> <head> <title>Scuffed HTTP</title> </head> <body> <h1>Scuffed HTTP</h1>");

    // get list of files
    DIR *d;
    struct dirent *dir;

    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {

            if (dir->d_name[0] == '.') {
                continue;
            }

            char *tmp = NULL;
            // build html around of files
            if (dir->d_type == DT_DIR) {
                // add directory link
                char possible_slash;

                // if last char is slash, remove it
                path[strlen(path) - 1] = (path[strlen(path) - 1] == '/') ? '\0' : path[strlen(path) - 1];
                // remove leading 0 from path
                if (path[0] == '.') path++;

                asprintf(&tmp, "<div><a href='%s/%s' style='color: red'> %s</a></div>", path, dir->d_name,
                         dir->d_name);
                strcat(dirs, tmp);
            } else if (dir->d_type == DT_REG) {
                // file link
                if (path[0] == '.') path++;
                asprintf(&tmp, "<div><a href='%s/%s' style='color: blue'> %s </a></div>", path, dir->d_name,
                         dir->d_name);
                strcat(files, tmp);
            }
            if (tmp != NULL) free(tmp);

        }
        closedir(d);
    }

    strcat(dest, dirs);
    strcat(dest, "<br>");
    strcat(dest, files);
    strcat(dest, "<a href='../'> up </a>");
    strcat(dest, "</body> </html>");

    // put it into dest_buf
    asprintf(dest_buf, "%s", dest);
}

