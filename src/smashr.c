/********************************************************************************
 *              smashr.c => Shell client for the smashr remote shell            *
 *                                                                              *
 *  Assignment: Lab 11 - IPC Remote Shell                                       *
 *  Author: Nathanael Smith and Austin Burdine                                  *
 *  Computer: W002-13 and Macbook                                               *
 *                                                                              *
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/simple-socket/client.h"

#define BUFSIZE 50

int main(int argc, char **argv) {
    char *hostname;
    int port;

    int fd;

    if (argc < 3) {
        fprintf(stderr, "You must supply a hostname and a port number");
        exit(1);
    }

    hostname = argv[1];
    port = atoi(argv[2]);

    fd = client_setup(hostname, port);

    FILE *connection = fdopen(fd, "rw");
    char buffer[BUFSIZE];

    while(fgets(buffer, BUFSIZE, connection) != NULL) {
        printf("%s", buffer);
    }

    return 0;
}
