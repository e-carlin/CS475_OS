/*
* Author: Evan Carlin
*/

#include "menu.h"
#include "defs.h"
#include "stat.h"
#include <stdio.h>
#include <string.h>


int main(){
	//Variable defs
	char userInputLine[MAX_INPUT_LEN]; //char[] for user input
	WordStats stats; //Word statistics struct

	//Initialize the struct to 0's
	stats = initStats(stats);

	printf("Starting the word processing engine...\n");
	printf("Enter strings (# to stop):\n");

	while(1){
		//Read user input
		fgets(userInputLine, MAX_INPUT_LEN, stdin);

		//Check if they want to get stats
		if(strcmp(userInputLine, "#\n") == 0){
			int userMenuOpt;

			//See how the user wants to proceed
			do{
				userMenuOpt = getMenuOpt();

				//They want to quit, so quit
				if(userMenuOpt == MENU_OPT_EXIT){
					printf("Goodbye.\n");
					return 0;
				}
				else if(userMenuOpt == MENU_OPT_VC){
					printVowelConsFreq(stats);
				}
				else if(userMenuOpt == MENU_OPT_WC){
					printWordCount(stats);
				}
				else if(userMenuOpt == MENU_OPT_HISTO){
					printHistogram(stats);
				}

			}while(userMenuOpt != MENU_OPT_RET); //They want to enter some more strings
		}

		//Update the word stats with this line
		stats = updateStats(stats, userInputLine);
		//Continue processing
	}
	return 1;
}