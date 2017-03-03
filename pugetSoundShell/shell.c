#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "stack.h"
#include "shell.h"

#define MOTDFile "/.psh_motd"

int i=0;
void processCommand(char *input, Stack *s){
	push(s, input);
	char *pathToExecutable;

	//First token is either the command we want to run (i.e. "ls") or the full path to the exeuctable
	char *arg = strtok(input, " ");
	int commType = isBuiltIn(arg, s);
	if(commType){
		//cd command so we need to process the rest of the string
		if(commType == 2){
			arg = strtok(NULL, " "); //get the path if there is one
			if(arg != NULL){
				chdir(arg);
				return;
			}
			if(commType == 3){
				return;
			}
			else{ //no path give so cd to $HOME 
				char *home = getenv("HOME");
				chdir(home);
			}
		}
		return;
	}
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
	int runInBackground = 0;
	char *nextArg;
	int argCount = 1;
	while(arg != NULL){
		nextArg = strtok(NULL, " ");
		if(strcmp(arg, "&") == 0 && nextArg == NULL){
			runInBackground = 1;
			arg = nextArg;
			continue;
		}
		args=realloc(args, sizeof(char*)*1);
		args[argCount] = realloc(args[argCount], sizeof(char*)*strlen(arg));
		args[argCount] = arg;
		argCount++;
		arg = nextArg;
	}
	args[argCount] = NULL;
	executeCommand(args[0], args, runInBackground);
	free(args);
	return;
}

void executeCommand(char* pathToExecutable, char** args, int runInBackground){
	pid_t childPid = fork();

	if(!fileExecPermission(pathToExecutable)){
		printf("Error: You don't have permission to execute this file\n");
		return;
	}
	else{

		if(runInBackground){
			if(childPid == 0){
				execv(pathToExecutable, args);
				return;
			}
			else{
				return;
			}
		}
		else{
			if(childPid == 0){ //If we are the child process
				execv(pathToExecutable, args);
				return;
			}
			else{
				wait(NULL);
				return;
			}
		}

	}

}


char *getFullPathToExecutable(char *execName){
	//First try current working directory
	if(execName[0] == '.'){
		int size = 256*sizeof(char*);
		char *cwd = (char*)malloc(size);
		getcwd(cwd, size);
		strcat(cwd, "/");
		strcat(cwd, &execName[2]);
		if(validFilePath(cwd)){
			return cwd;
		}
	}
	//Not in cwd so try $PATH
	else{
		//Get the $PATH
		char *PATH = strdup(getenv("PATH"));
		//Different path's to try
		char *pathToTry;

		//Split $PATH on : delim
		while( (pathToTry = strsep(&PATH,":")) != NULL ){
			//Get the full path to the executable
			//malloc space for the full path plus the executable name 
			char *fullPathToExecutable = (char*)malloc(sizeof(char) * (strlen(pathToTry) +strlen(execName) + 2)); //+2 = 1 for/ and 1 for \0 
			//Add the path to the full path
			strcpy(fullPathToExecutable, pathToTry);
			//Add / 
			strcat(fullPathToExecutable, "/");
			//Add the name of the executable we want to run
			strcat(fullPathToExecutable, execName);

			//If the path is valid
			if(validFilePath(fullPathToExecutable)){
					return fullPathToExecutable;
			}
			free(fullPathToExecutable);
		}
	}
	printf("Error: %s command not found\n", execName);
	return NULL;
}

int isBuiltIn(char *command, Stack *s){
	if(strcmp(command, "exit") == 0){
		exit(0);
	}
	else if(strcmp(command, "pwd") == 0){
		int size = 256*sizeof(char*);
		char *cwd = (char*)malloc(size);
		getcwd(cwd, size);
		printf("%s\n", cwd);
		free(cwd);
		return 1;
	}
	else if(strcmp(command, "cd") == 0){
		return 2;
	}
	else if(strcmp(command, "history") == 0){
		//TODO: print history
		printStack(*s, HISTORY_LEN);
		return 3;
	}
	return 0;
}

void printMOTD(){
	char home[150];
	char * MOTDPath = getenv("HOME");
	strcat(home, MOTDPath);
	strcat(home, MOTDFile);
	if(validFilePath(MOTDPath) && fileReadPermission(MOTDPath)){
		int c;
		FILE *file;
		file = fopen(home, "r");
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