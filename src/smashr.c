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

/* our main function */
int main(int argc, char **argv) {
    char *hostname;
    int port;

    int fd;

    if (argc < 3) {
        fprintf(stderr, "You must supply a hostname and a port number\n");
        exit(1);
    }

    hostname = argv[1];
    port = atoi(argv[2]);

    fd = client_setup(hostname, port);

    /* our line i/o buffer and read length */
    int len = 0;
    char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);

    /* needed for select */
    fd_set rfds;
    int retval;
    
    while(1) {
        /* we're using select() to monitor both sockets at once */
        /* let's follow an example: http://www.tutorialspoint.com/unix_system_calls/_newselect.htm */
        /* clear the set of sockets */
        FD_ZERO(&rfds);
        /* add both sockets to the list */
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(fd, &rfds);

        /* wait for a socket to have something */
        retval = select(fd + 1, &rfds, NULL, NULL, NULL);

        if (retval == -1) {
            perror("select()");
        }
        else if (FD_ISSET(fd, &rfds)) {
            /* data is available from the socket */
            while((len = read(fd, buffer, BUFSIZE)) > 0) {
                /* our exit code */
                if (buffer[0] == 4) {
                    close(fd);
                    exit(0);
                }
                /* we need to append a null terminator to the string */
                if (len < BUFSIZE) {
                    buffer[len] = '\0';
                    write(STDOUT_FILENO, buffer, len);
                }
                else {
                    write(STDOUT_FILENO, buffer, len);
                    write(STDOUT_FILENO, '\0', 1);
                }
                
                memset(buffer, 0, BUFSIZE);

                if (len != BUFSIZE) {
                    break;
                }
            }
        }
        else if (FD_ISSET(STDIN_FILENO, &rfds)) {
            /* data is available from stdin */
            while((len = read(STDIN_FILENO, buffer, BUFSIZE)) > 0) {
                /* we need to append a null terminator to the string */
                if (len < BUFSIZE) {
                    buffer[len] = '\0';
                    write(fd, buffer, len);
                }
                else {
                    write(fd, buffer, len);
                    write(fd, '\0', 1);
                }
                
                memset(buffer, 0, BUFSIZE);

                if (len != BUFSIZE) {
                    break;
                }
            }
        }
    }
}

