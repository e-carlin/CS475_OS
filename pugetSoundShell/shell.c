/*
* @author Evan Carlin
* A simple shell emulator
* It takes in user given commands and spawns off process to run them.
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "stack.h"
#include "shell.h"

//Path to the message of the day
#define MOTDFile "/.psh_motd"

/*
* Given a user command parses it and takes corresponding action
* @param input the string command input (i.e. cd /home/xinu)
* @param s a pointer to the stack to store the list of commands
*/
void processCommand(char *input, Stack *s){
	push(s, input);
	char *pathToExecutable;
	pathToExecutable = (char*)malloc(sizeof(char)*MAX_INPUT_LEN);
	//First token is either the command we want to run (i.e. "ls") or the full path to the exeuctable
	char *arg;
	arg = (char*)malloc(sizeof(char)*MAX_INPUT_LEN);
	strcpy(arg, strtok(input, " "));
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
		strcpy(pathToExecutable, arg);
		}
	//Full path to the executable needs to be found
	else{
		pathToExecutable = getFullPathToExecutable(arg);
		if(pathToExecutable == NULL)
			return;
	}

	int argsCount =1;
	int runInBackground = 0;

	//Allocate space for args
	char **args;
	args=malloc(sizeof(char*)*2); //1 for executable path,  1 for final NULL
	args[0] = malloc(sizeof(char*)*strlen(pathToExecutable));
	
	//First arg is the path to the executable
	args[0] = pathToExecutable;
	arg = strtok(NULL, " ");

	//Process the rest of the args
	while(arg != NULL){
		if(strcmp(arg, "&") == 0){
			runInBackground = 1;
			arg = strtok(NULL, " ");
			continue;
		}
		args = realloc(args, sizeof(char*));
		args[argsCount] = realloc(args[argsCount], sizeof(char)*strlen(arg));
		args[argsCount] = arg;
		argsCount++;
		arg = strtok(NULL, " ");
	}
	args = realloc(args, sizeof(char*));
	args[argsCount] = NULL;
	executeCommand(args[0], args, runInBackground);
	

	free(arg);
	free(args);
	return;
}

/*
* Spawn a new process to execute the command
* @param pathToExecutable the full path to the executable we wish to run
* @param the args for the executable
* @param runInBackground if 1 process will be run in background (wait() not called)
*/
void executeCommand(char* pathToExecutable, char** args, int runInBackground){
	pid_t childPid = fork();

	if(!fileExecPermission(pathToExecutable)){
		printf("Error: You don't have permission to execute %s\n", pathToExecutable);
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


/*
* Given the name of an executable checks cwd and $PATH to
* try to find the location of the executable
* @param execName the name of the executable
*/
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

/*
* Checks to see if the given command is one of the builtins
* pwd, exit, cd, and history
* @param command the command we are checking 
* @param s a stack so we can print the history
* @return 1 on pwd. 2 on cd, 3 on history, 0 for not a builtin
*/
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
		printStack(*s, HISTORY_LEN);
		return 3;
	}
	return 0;
}

/*
* Trys to print the messaage of the day
*/
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

/*
* Sees if the given file path is valid
* @param path the path to the file
* @return 1 on valid, 0 otherwise
*/
int validFilePath(char *path){
	return (!access( path, F_OK )) ? 1 : 0;
}

/*
* Sees if we have read permissions for given file
* @param path the path to the file
* @return 1 on permissions granted, 0 otherwise
*/
int fileReadPermission(char *path){
	return (!access( path, R_OK )) ? 1 : 0;
}

/*
* Sees if we have execute permissions for the given file
* @param path the path to the file
* @return 1 on permission to execute, 0 otherwise
*/
int fileExecPermission(char *path){
	return (!access( path, X_OK )) ? 1 : 0;
}