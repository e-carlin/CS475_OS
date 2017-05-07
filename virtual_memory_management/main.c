#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vmm.h"

#define usage "Usage: ./vmm [-p num_pages] [-f num_frames] [-b block_size] [-r rep_policy] <inst_file>"


int main(int argc, char *argv[]){

	// Command line args
	char *inst_file_path = "/home/xinu/CS475_OS/virtual_memory_management/input.txt";

	// This MUST happen before any process of the instruction occurs
	// It sets up the page and frame tables
	create_tables(num_pages, num_frames);

	// File read in vars
	FILE *inst_file;
	inst_file = fopen(inst_file_path, "r");
    char buffer[255];

	// Read in instruction file
 	while (fgets(buffer, sizeof buffer, (FILE*)inst_file) != NULL){

		// Send instruction to the VMM for processing
		process_inst(buffer);
	 }
 	if (feof(inst_file)){
		printf("*****EOF*****");
 	}
 	else{
	 printf("Error while reading instruction file. Exiting...");
	 return -1;
 	}

	return 0;

}
