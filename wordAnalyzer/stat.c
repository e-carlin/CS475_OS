/*
* Author: Evan Carlin
* A class that updates a WordStat by processing a given string
*/

#include "stat.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Helper method prototypes
static int isWordAlpha(const char[]);
static int getMostFreqChar(WordStats stats);

/*
* Initializes all of the counts in a WordStat to 0
*/
WordStats initStats(WordStats stats){
	//Initialize histogram to 0
	int i;
	for(i=0; i<ALPHABET_SIZE; i++){
		stats.histo[i] = 0;
	}

	stats.wordCount = 0;
	stats.vowelCount = 0;
	stats.consonantCount = 0;

	return stats;
}

/*
* Given a string updates the WordStats struct accoringly
*/
WordStats updateStats(WordStats stats,  const char userLine[]){

	//Copy the string so strtok doesn't mutilate it
	char str[MAX_INPUT_LEN];
	strcpy(str, userLine);

	//Process the first and subsequent words
	char *token = strtok(str, " \n");
	while(token != NULL){
		//process only alphanumeric tokens
		if(isWordAlpha(token)){
			stats = incrementWordCount(stats); //stats.wordCount++
			stats = updateVowelConsCount(stats, token);
			stats = updateHistogramCount(stats, token);
		}
		//Get the next token
		token = strtok(NULL, " \n");
	}
	return stats;
}

/*
* Updates the counts of each char in the histo[]
*/
WordStats updateHistogramCount(WordStats stats, const char word[]){
	int i;
	for(i=0; i<strlen(word); i++){
		char c = tolower(word[i]);
		stats.histo[c-97]++;
		}
	return stats;
}

/*
* Increments the word count by +1
*/
WordStats incrementWordCount(WordStats stats){
	stats.wordCount++;
	return stats;
}

/*
* Updates the vowel and consonant count from the supplied word
*/
WordStats updateVowelConsCount(WordStats stats, const char word[]){
	int i;
	for(i=0; i<strlen(word); i++){
		char charAsLower = tolower(word[i]);
		int isVowel = (charAsLower == 'a' || charAsLower == 'e' || charAsLower == 'i' || charAsLower == 'o' || charAsLower == 'u');
		if(isVowel){
			stats.vowelCount ++;
		}
		else{
			stats.consonantCount++;
		}
	}
	return stats;
}

/*
* Prints the frequency of vowels and consonants
*/
void printVowelConsFreq(WordStats stats){
	float totalChars = stats.vowelCount + stats.consonantCount;

	printf("\nVowels = %d (%0.2f%%), Consonants = %d (%0.2f%%), Total = %0.0f\n", 
		stats.vowelCount, (stats.vowelCount/totalChars)*100, 
		stats.consonantCount, (stats.consonantCount/totalChars)*100,
		totalChars);
}

/*
* Prints the total number of valid words given by the user
*/
void printWordCount(WordStats stats){
	printf("\nWord count: %d\n", stats.wordCount);
}

/*
* Prints a histogram (vertical bars) of the frequency of all
* the chars given by the user.
*/
void printHistogram(WordStats stats){
	int mostFreqChar = getMostFreqChar(stats);
	int i, j;
	for(i=mostFreqChar; i>-2; i--){
		for(j=0; j<ALPHABET_SIZE; j++){
			//Printing *'s
			if(i>0){
					if(stats.histo[j] >= i){
					printf("* ");
				}
				else{
					printf("  ");
				}
			}
			//Print the letters along the x-axis
			if(i == 0){
				printf("%c ", j+97);
			}
			//Print the int freq of the
			if(i == -1){
				printf("%d ", stats.histo[j]);
			}
		}
		printf("\n");
	}
}

/*
*======== HELPERS ========
*/

/*
* Gets the number of appearances of the most frequently
* appearing character
*/
static int getMostFreqChar(WordStats stats){
	int max = 0;
	int i;
	for(i=0; i<ALPHABET_SIZE; i++){
		if(stats.histo[i] > max)
			max = stats.histo[i];
	}
	return max;
}

/*
* Determines if a word contains only letters A-Z and a-z
* 1 if it does 0 otherwise
*/
static int isWordAlpha(const char word[]){
	int i;
	for(i=0; i<strlen(word); i++){
		if(isalpha(word[i]) == 0){ //Char i wasn't alphanumeric
			return 0;
		}
	}
	return 1;
}