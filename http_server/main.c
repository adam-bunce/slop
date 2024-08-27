#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "files.h"
#include "http.h"

void error(char *err) {
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}

int get_port(char *port_str) {
    char *pEnd = NULL;
    errno = 0;
    int port = (unsigned short) strtol(port_str, &pEnd, 10);
    if (errno != 0) {
        char *p = malloc(sizeof(char) * 100);
        sprintf(p, "Port conversion failure (%d): %s\n", errno, strerror(errno));
        error(p);
        free(p);
    }

    return port;
}


void *handle_client(void *arg) {
    int ns = (int) (intptr_t) arg;

    size_t buf_size = 1000 * sizeof(char);
    char *request_buf = malloc(buf_size);

    // get client msg
    if (recv(ns, request_buf, buf_size, 0) == -1)
        error("failed to recv");


    struct request req;
    parse_request(request_buf, &req);
    printf("%s %s\n", http_code_lookup[req.method], req.path);

    if (is_dir(req.path)) {
        // file not found (failed to populate)
        char *dir_content_dest_buf = NULL;
        build_dir_response_body(&dir_content_dest_buf, req.path);

        struct file_info fi;

        char *dest_buf = NULL;
        fi.file_content = dir_content_dest_buf;

        // cant assign[40]
        file_ext_to_type(".html", fi.file_type);
        fi.file_length = strlen(fi.file_content) * sizeof(char);
        build_http_response(&dest_buf, &fi, OK);

        ssize_t sent = 0;
        if ((sent = send(ns, dest_buf, strlen(dest_buf), 0)) == -1)
            error("Failed to send to client");

        printf("sent %lu bytes\n", sent);

        close(ns);
        free(dest_buf);
        free(request_buf);

        pthread_exit(NULL);
    }


    struct file_info fi;
    if (populate_file_struct(&fi, req.path) == EXIT_FAILURE) {
        // file not found (failed to populate)
        printf("404 %s not found\n", req.path);

        // 404
        char *dest_buf = NULL;
        get_404_response(&dest_buf);

        ssize_t sent = 0;
        if ((sent = send(ns, dest_buf, strlen(dest_buf), 0)) == -1)
            error("Failed to send to client");
        printf("sent %lu bytes\n", sent);


        close(ns);
        free(dest_buf);
        free(request_buf);

        pthread_exit(NULL);
    }

    char *dest_buf = NULL;
    int resp_size = build_http_response(&dest_buf, &fi, OK);

    ssize_t sent = 0;
    if ((sent = send(ns, dest_buf, resp_size * sizeof(char) + fi.file_length * sizeof(char), 0)) == -1)
        error("Failed to send to client");
    printf("sent %lu bytes\n", sent);


    close(ns);
    free(dest_buf);
    // if we dont read the file, then we cant free it big dog
    if (fi.file_content != NULL) free(fi.file_content);
    free(request_buf);

    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    unsigned short port;
    struct sockaddr_in client;
    struct sockaddr_in server;
    int s; // socket for accepting connections
    int ns; // socket connected to client
    socklen_t nameLen; // length of client name

    if (argc != 2) {
        char *err_msg = NULL;
        asprintf(&err_msg, "Usage: %s <port>", argv[0]);
        error(err_msg);
    }
    port = get_port(argv[1]);
    printf("using port: %u\n", port);

    // get socket to accept connections on
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error("Failed to initialize socket");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    // bind server to socket we got
    if ((bind(s, (struct sockaddr *) &server, sizeof(server))) == -1)
        error("Failed to bind server");

    // listen for connections on that socket
    if (listen(s, 1) == -1)
        error("Server failed to listen");


    printf("Starting server...\n");
    while (true) {
        // accept a connection
        nameLen = sizeof(client);
        if ((ns = accept(s, (struct sockaddr *) &client, &nameLen)) == -1)
            error("Failed to accept client");

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *) (intptr_t) ns);
        pthread_detach(thread_id);
    }


    printf("exiting\n");
    return EXIT_SUCCESS;
}