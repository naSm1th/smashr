/*****************************************************************************
 * cd.c - the Smith Shell's implementation of the cd command                 *
 *     changes the current working directory according the POSIX specs       *
 *                                                                           *
 * By Nathanael A. Smith - nasmith@olivet.edu                                *
 * Submitted as part of Lab 9 of CSIS-381 - Systems Programming              *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

/* Gets the current working directory */
char *getCurrentWorkingDirectory() {
    char *cwd;

    cwd = getenv("PWD");

    if (cwd != NULL) {
        return cwd;
    }

    return (char *) getcwd(NULL, 0);
}

/* changes the current working directory */
/* complies with the POSIX standards for the cd command */
int cd(char *args) {
    char *pwd;
    int cdResult;

    pwd = getCurrentWorkingDirectory();

    /* If no args supplied */
    if (args == NULL) {
        char *home = getenv("HOME");

        if (home == NULL) {
            /* if no arguments and no $HOME */
            /* do nothing */
            return 0;
        }

        /* if no arguments and $HOME not empty */
        /* go to $HOME */
        cdResult = chdir(home);

        if (!cdResult) {
            setenv("PWD", home, 1);
            setenv("OLDPWD", pwd, 1);
            return 0;
        }

        // Something errored with chdir, throw error
        strerror(errno);
        return 1;
    }

    /* If args is just a '-', go to old pwd */
    if (args[0] == '-' && args[1] == '\0') {
        char *oldPwd = getenv("OLDPWD");

        // Old PWD doesn't exist, exit
        if (oldPwd == NULL) {
            return 0;
        }

        cdResult = chdir(oldPwd);

        if (!cdResult) {
            setenv("OLDPWD", pwd, 1);
            setenv("PWD", oldPwd, 1);
            return 0;
        }

        // something errored with chdir, throw error
        strerror(errno);
        return 1;
    }

    char *newPwd = realpath(args, NULL);

    cdResult = chdir(newPwd);

    if (!cdResult) {
        setenv("OLDPWD", pwd, 1);
        setenv("PWD", newPwd, 1);
        return 0;
    }

    strerror(errno);
    return 1;
    /* if directory begins with / */
    /* set curpath to directory */

    /* else */
    return 0;
}
