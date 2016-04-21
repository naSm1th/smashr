/*****************************************************************************
 * cd.c - the Smith Shell's implementation of the cd command                 *
 *     changes the current working directory according the POSIX specs       *
 *                                                                           *
 * By Nathanael A. Smith - nasmith@olivet.edu                                *
 * Submitted as part of Lab 9 of CSIS-381 - Systems Programming              *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

/* changes the current working directory */
/* complies with the POSIX standards for the cd command */
int cd(char *args) {
    /* if no arguments and no $HOME */
    /* do nothing */

    /* if no arguments and $HOME not empty */
    /* go to $HOME */

    /* if directory begins with / */
    /* set curpath to directory */
    
    /* else */
    return 0;
}
