/*****************************************************************************
 * shell.c - a simple Unix shell                                           *
 *                                                                           *
 * By Nathanael A. Smith - nasmith@olivet.edu                                *
 * Submitted as part of Lab 9 of CSIS-381 - Systems Programming              *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "shell.h"

/* our main function */
int main (int argc, char **argv) {
	/* our current working directory */
	char *cwd;
	/* the line buffer and line string */
	char buffer[BUFSIZE];
	char *line = NULL;
	/* the filename and arguments */
	char **args;
	
	/* loop forever */
	while (1) {
		/* get the current working directory */
		cwd = (char *)malloc(CWD_LEN*sizeof(char));
		int i;
		for (i = 2; getcwd(cwd, (i-1)*CWD_LEN*sizeof(char)) == NULL;
				i++) {
			cwd = (char *)realloc(cwd, i*CWD_LEN*sizeof(char));
		}
		/* print the prompt */
		printf("SmSH:%s>", cwd);
		/* get user input and parse */
		while (1) {
			fgets(buffer, BUFSIZE, stdin);
			/* append line to line array */
			if (line == NULL) {
				line = (char *)malloc(strlen(buffer) + 1);
				*line = '\0';
			}
			else {
				line = (char *)realloc(line, strlen(line) 
						+ strlen(buffer) + 1);
			}
			
			line = strcat(line, buffer);

			/* see if line is done */
			if (strlen(buffer) + 1 <  BUFSIZE || 
					(strlen(buffer) + 1 == BUFSIZE && 
					 buffer[BUFSIZE-2] == '\n')) {
				/* we're done with this line */
				break;
			}
		}
		
		char *tmpLine = line;
		
		/* split the line into the file and args */
		/* thanks to http://www.tutorialspoint.com/c_standard_library/
		   	c_function_strtok.htm */
		args = (char **)malloc(2 * sizeof(char *));
		args[0] = strtok(tmpLine, " \n\t");

		/* check for blank line */
		if (args[0] == '\0') {
			continue;
		}
		
		for (i = 1; (args[i] = strtok(NULL, " \n\t")) != NULL; i++) {
			args = realloc(args, (i + 2) * sizeof(char *));
		}
		args[i] = (char *)NULL;

		/* execute the line */
		execute(args, i);

		/* clean up */
		free(args);
		free(line);
		free(cwd);
		line = NULL;
	}
}

/* executes a list of arguments */
void execute(char **args, int numArgs) {
	/* find/replace pipes */
	int numPipes = 0;
	int j;
	for (j = 0; j < numArgs; j++) {
		if (strcmp(args[j], "|") == 0) {
			/* we haz teh pipe! */
			if (j != 0) {
				if (args[j-1] != NULL && args[j+1] != NULL) {
					numPipes++;
					args[j] = (char *)NULL;
				}
			}
		}
	}

	/* let's see if we need to handle the command internally */
	/* commands include: cd, exit */
	if (strcmp(args[0], "cd") == 0) {
		/* TODO: change the working directory */
	}
	else if (strcmp(args[0], "exit") == 0) {
		/* exit */
		exit(0);
	}

	else {
		/* external command */
		int pidPipe[2];
		int pid;
		pipe(pidPipe);

		executeExternal(args, numPipes, NULL, pidPipe);

		/* this section is rather hacky... */
		/* I could not get my code to completely wait for all */
		/*    children to finish executing/writing to stdout */
		/* adding a usleep seems to help... but it's not ideal */
		read(pidPipe[0], &pid, sizeof(pid));
		
		waitpid(pid, NULL, 0);
		
		while ((pid = wait(NULL)) != -1) {
		}
		
		if (numPipes != 0) {
			usleep(100000);
		}
	}
}

/* execute an internal command with pipes */
void executeExternal(char **args, int numPipes, int *myPipe, int *pidPipe) {
	/* fork and execute */
	if (fork()) {
		/* we are the parent */
	}
	else {
		/* we are the child process */
		if (myPipe != NULL) {
			/* close the writing pipe */
			close(myPipe[1]);
			/* replace stdin with the pipe */
			dup2(myPipe[0], STDIN_FILENO);
			close(myPipe[0]);
			
		}

		/* make new pipe for child process */
		if (numPipes > 0) {
			int newPipe[2];
			pipe(newPipe);
		
			/* execute the next command */
			char **tmpArgs = args;

			while (tmpArgs[0] != NULL) {
				tmpArgs++;
			}
			while (tmpArgs[0] == NULL) {
				tmpArgs++;
			}
			
			executeExternal(tmpArgs, numPipes-1, newPipe, pidPipe);
		
			/* replace stdout with this pipe */
			dup2(newPipe[1], STDOUT_FILENO);
			close(newPipe[1]);
			close(newPipe[0]);
	
		}
		if (numPipes == 0) {
			int pid = getpid();
			write(pidPipe[1], &pid, sizeof(pid_t));
		}
		close(pidPipe[1]);
		close(pidPipe[0]);
	
		/* execute file with args */
		int returnStatus = execvp(args[0], args);

		if (returnStatus < 0) {
			perror(args[0]);
		}
		exit(0);
	}
}
