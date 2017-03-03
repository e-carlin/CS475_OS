#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"

#define MOTDFile "/.psh_motd"

void processCommand(char *input){
	char *pathToExecutable;

	//First token is either the command we want to run (i.e. "ls") or the full path to the exeuctable
	char *arg = strtok(input, " ");
	//If the token starts with a / then that means we have the full path to the executable
	if(arg[0] == '/'){
		pathToExecutable = arg;
		}
	//Full path to the executable needs to be found
	else{
		pathToExecutable = getFullPathToExecutable(arg);
		if(pathToExecutable == NULL)
			return;
	}
	char **args;
	args=malloc(sizeof(char*)*2); //1 for executable path,  1 for final NULL
	args[0] = malloc(sizeof(char*)*strlen(pathToExecutable));
	args[0] = pathToExecutable;

	arg = strtok(NULL, " ");
	int argCount = 1;
	while(arg != NULL){
		args=realloc(args, sizeof(char*)*1);
		args[argCount] = realloc(args[argCount], sizeof(char*)*strlen(arg));
		args[argCount] = arg;
		argCount++;
		arg = strtok(NULL, " ");
	}
	int i;
	args[argCount] = NULL;
	executeCommand(args[0], args, 1);
	free(args);
}

void executeCommand(char* pathToExecutable, char** args, int runInBackground){
	pid_t childPid = fork();

	if(!fileExecPermission(pathToExecutable)){
		printf("Error: You don't have permission to execute this file\n");
		return;
	}
	else{
		printf("Executing command... ");
		if(runInBackground){
			printf("in background \n");
			if(childPid == 0){
				int status = execv(pathToExecutable, args);
				printf("Status %d\n", status);
			}
			else{
				return;
			}
		}
		else{
			printf("in foreground\n");
			if(childPid == 0){ //If we are the child process
				int status = execv(pathToExecutable, args);
				printf("Status %d\n", status);
			}
			else{
				printf("I am the parent. Calling wait...\n");
				wait(NULL);
				return;
			}
		}

	}

}


char *getFullPathToExecutable(char *execName){
	//Get the $PATH
	char *PATH = strdup(getenv("PATH"));
	//Different path's to try
	char *pathToTry;

	//Split $PATH on : delim
	while( (pathToTry = strsep(&PATH,":")) != NULL ){
		//Get the full path to the executable
		//malloc space for the full path plus the executable name 
		printf("Path to try %s\n", pathToTry);
		char *fullPathToExecutable = (char*)malloc(sizeof(char) * (strlen(pathToTry) +strlen(execName) + 2)); //+2 = 1 for/ and 1 for \0 
		//Add the path to the full path
		strcpy(fullPathToExecutable, pathToTry);
		//Add / 
		strcat(fullPathToExecutable, "/");
		//Add the name of the executable we want to run
		strcat(fullPathToExecutable, execName);

		//If the path is valid
		if(validFilePath(fullPathToExecutable)){
			printf("Found executable\n");
			printf("It is %s\n", fullPathToExecutable);
				return fullPathToExecutable;
		}
		free(fullPathToExecutable);
	}
	printf("Error: %s command not found\n", execName);
	return NULL;
}

void printMOTD(){
	char * MOTDPath = getenv("HOME");
	strcat(MOTDPath, MOTDFile);
	if(validFilePath(MOTDPath) && fileReadPermission(MOTDPath)){
		int c;
		FILE *file;
		file = fopen(MOTDPath, "r");
		if (file) {
		    while ((c = getc(file)) != EOF)
		        putchar(c);
		    fclose(file);
		}
	}
}

int validFilePath(char *path){
	return (!access( path, F_OK )) ? 1 : 0;
}

int fileReadPermission(char *path){
	return (!access( path, R_OK )) ? 1 : 0;
}

int fileExecPermission(char *path){
	return (!access( path, X_OK )) ? 1 : 0;
}