struct Command{
	char *pathToExecutable;
	int numArgs;
	int runInBackground;
	char *args[0];
};

int validFilePath(char *);
int fileReadPermission(char *);
int fileExecPermission(char *);
void printMOTD();
void processCommand(char *);
void executeCommand(char*, char**, int);
char *getFullPathToExecutable(char *);
struct Command *initializeCommand(struct Command*);

#define MAX_NUM_ARGS 25
