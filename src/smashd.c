/********************************************************************************
 *              smashd.c => Shell server for the smashr remote shell             *
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

#include "../lib/simple-socket/server.h"

int serverFd;

void shell_exec(int fd) {
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDIN_FILENO);
    close(fd);

    system("sh");
}

int main(int argc, char **argv) {
    int port;

    if (argc > 1) {
        port = atoi(argv[1]);
    } else {
        port = 2368;
    }

    serverFd = server_setup(port);

    printf("Smash dameon listening on port %d\n", port);

    server_listen(&shell_exec);

    exit(1);
}
