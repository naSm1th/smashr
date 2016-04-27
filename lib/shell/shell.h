/*****************************************************************************
 * smsh.h - the main header file for SmSH - the Smith Shell                 *
 *     (Pronounced Smoosh)                                                   *
 *                                                                           *
 * By Nathanael A. Smith - nasmith@olivet.edu                                *
 * Submitted as part of Lab 9 of CSIS-381 - Systems Programming              *
 *****************************************************************************/
#define BUFSIZE 1024

void execute(char **args, int numArgs);
void executeExternal(char **args, int numPipes, int *myPipe, int *pidPipe);

/* cd functions */
char *getCurrentWorkingDirectory();
int cd(char *args);
