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

char *resp =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 31\r\n"
        "\r\n"
        "<html> <h1>Hello </h1> </html>\n"
        "\r\n";


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

void *handle_client(void *thread_id) {
    return NULL;
}


int main(int argc, char **argv) {
    unsigned short port;
    struct sockaddr_in client;
    struct sockaddr_in server;
    int s; // socket for accepting connections
    int ns; // socket connected to client
    socklen_t nameLen; // length of client name

    printf("bytes: %lu\n", strlen("<html> <h1>Hello </h1> </html>\n"));

    if (argc != 2) {
        error("Usage: ./server port");
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


    while (true) {
        printf("getting new conn\n");
        // accept a connection
        nameLen = sizeof(client);
        if ((ns = accept(s, (struct sockaddr *) &client, &nameLen)) == -1)
            error("Failed to accept client");
        printf("connected to client");


        // TODO: handle connection in thread
//        pthread_t thread_id;
//        pthread_create(&thread_id, NULL, handle_client, (void *) ns);
//        pthread_detach(thread_id);

        size_t buf_size = 1000 * sizeof(char);
        char *buf = malloc(buf_size);
        // get client msg
        if (recv(ns, buf, buf_size, 0) == -1)
            error("failed to recv");
        printf("received from client, '%s'\n", buf);

        ssize_t sent = 0;
        if ((sent = send(ns, resp, strlen(resp), 0)) == -1)
            error("Failed to send to client");
        printf("sent response (%zd)\n", sent);

        printf("%s", resp);

        close(ns);
        free(buf);
    }


    printf("exiting\n");
    return EXIT_SUCCESS;
}