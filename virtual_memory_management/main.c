#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "vmm.h"

#define usage "Usage: ./vmm [-p num_pages] [-f num_frames] [-b block_size] [-r rep_policy] <inst_file>"


int main(int argc, char *argv[]){

	int i;

	if(argc < 2){
		printf("%s\n", usage);
		exit(-1);
	}
	for(i = 1; i < argc-1; i+=2){

		if(strcmp(argv[i], "-p") == 0){

			printf("-p found\n");
			num_pages = atoi(argv[i+1]);
		}
		if(strcmp(argv[i], "-f") == 0){

			num_frames = atoi(argv[i+1]);
		}
		if(strcmp(argv[i], "-b") == 0){

			block_size = atoi(argv[i+1]);
		}
		if(strcmp(argv[i], "-r") == 0){

			rep_policy = argv[i+1];
		}
	}

	//Check if file exists
	if( access( argv[argc-1], F_OK ) != -1 ) {
	    
	    	// This MUST happen before any process of the instruction occurs
	    	// It sets up the page and frame tables
	    	create_tables(num_pages, num_frames);

	    	// File read in vars
	    	FILE *inst_file;
	    	inst_file = fopen(argv[argc-1], "r");
	        char buffer[255];

	        //Check block and frame size are within bounds for 32-bit addresses
	        if(((int)round((log(num_pages) / log(2)))) + ((int)round((log(block_size) / log(2)))) > 32){

	        	printf("Block size and number of pages are too large for 32-bit addresses. Exiting...\n");
	        	exit(-1);
	        }
	    	// Read in instruction file
	     	while (fgets(buffer, sizeof buffer, (FILE*)inst_file) != NULL){

	    		// Send instruction to the VMM for processing
	    		process_inst(buffer);
	    	 }
	     	if (!feof(inst_file)){
	    	 printf("Error while reading instruction file. Exiting...");
	    	 return -1;
	     	}

	     	printf("inst_count=%d (reads=%f%%, writes=%f%%), page_faults=%d (%f%%), replacements=%d (%f%%)\n",
	     	 num_inst, num_reads/(double)num_inst*100, num_writes/(double)num_inst*100, num_page_faults, num_page_faults/(double)num_inst*100, num_replacements, num_replacements/(double)num_inst*100);
	    	return 0;
	} 
	else {
	    printf("File '%s' doesn't exist. Exiting...\n", argv[argc-1]);
	}

}
