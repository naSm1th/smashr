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
char *cmd;

/* this will be executed in the child process */
void shell_exec(int fd) {
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDERR_FILENO);

    setbuf(stdout, NULL);
    system(cmd);
    
    /* tell the client to close the socket */
    /* we are sending the end of transmission character */
    char data[] = {4, '\0'};
    write(STDIN_FILENO, data, 1);
    close(fd);
}

/* our main function */
int main(int argc, char **argv) {
    int port;

    if (argc == 2) {
        cmd = argv[1];
        port = 2368;
    }
    else if (argc == 3) {
        port = atoi(argv[1]);
        cmd = argv[2];
    }
    else {
        cmd = "./shell";
        port = 2368;
    }

    /* set up the socket */
    serverFd = server_setup(port);

    printf("Smash daemon listening on port %d\n", port);
    
    /* loop until ctrl-c, adding clients */
    server_listen(&shell_exec);

    exit(1);
}
