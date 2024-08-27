#pragma once

#include "files.h"

enum Status {
    OK = 200,
    NOT_FOUND = 404,
    SERVER_ERROR = 500,
};

static char *http_resp_message_lookup[] = {
        [OK] = "OK",
        [NOT_FOUND] = "Not Found",
        [SERVER_ERROR] = "Internal Server Error"
};

enum Method {
    GET = 0,
    PUT,
    POST,
    DELETE,
    HEAD,
    OPTIONS,
};

static char *http_code_lookup[] = {
        [GET] = "GET",
        [PUT] = "PUT",
        [POST] = "POST",
        [DELETE] = "DELETE",
        [HEAD] = "HEAD",
        [OPTIONS] = "OPTIONS"
};

struct request {
    // hard coding these sizes seem cringe
    // but malloc'ing the same size is also cringe
    char path[100];
    enum Method method;
};


int build_http_response(char **dest_buf, struct file_info *file_info, enum Status status);

void get_404_response(char **dest_buf);

void parse_request(char *request_buf, struct request *dest);

void build_dir_response_body(char **dest_buf, char *path);
