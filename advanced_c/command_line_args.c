#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv) {
    // flag lives here -a, whatever
    // no --foo, only -f
    int option;

    while ((option = getopt(argc, argv, ":a:b")) != -1) {
        switch (option) {
            case 'a':
                printf("i got a: %s\n", optarg);
                break;
            case 'b':
                printf("i got b\n");
                break;
            case '?':
                printf("ERROR\n");
                break;
            case ':':
                printf("expected argument\n");
        }
    }

    for (int i = optind; i < argc; i++)
        printf("%d %s\n", i, argv[i]);


    return 0;
}