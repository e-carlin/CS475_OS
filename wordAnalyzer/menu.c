/*
* Author: Evan Carlin
* Prompts the user for a menu option and returns their selection
*/
#include "menu.h"
#include <stdio.h>

int getMenuOpt(){
	int userOption = -1;

	//Keep prompting the user until a valid number is entered
	while(1){
		//Prompt the user for their choice
		printf("\n\n *** Word Stat Menu ***\n");
		printf("Please enter an option to continue.\n");
		printf("Press 1 to get vowel and consonant frequency.\n");
		printf("Press 2 to print out the word count.\n");
		printf("Press 3 to print out a histogram of letter-use frequencyy.\n");
		printf("Press 4 to continue entering more strings.\n");
		printf("Press 5 to QUIT.\n");

		//Read in the user choice
		printf("Enter your choice: ");
		scanf("%d", &userOption);

		if(userOption == MENU_OPT_VC ||
			userOption == MENU_OPT_WC ||
			userOption == MENU_OPT_HISTO ||
			userOption == MENU_OPT_RET || 
			userOption == MENU_OPT_EXIT){
			break;
		}

		else
			printf("%d is not a vaild number!\n\n", userOption);

	}

	return userOption;
}