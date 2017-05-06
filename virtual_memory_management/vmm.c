#include <stdio.h>
#include <stdlib.h>
#include "vmm.h"

//Tables
PTE *page_table;// = (PTE*) malloc(sizeof(PTE*) * num_pages);
FTE *frame_table;// = (FTE*) malloc(sizeof(FTE*) * num_frames);

/**
* Creates the page_table and frame_table of proper size.
* @param num_pages, the number of page table entries to allocate in the page_table.
* @param num_frames, the number of frame table entries to allocate in the frame_table.
*/
void create_tables(int num_pages, int num_frames){
    page_table = (PTE*) malloc(sizeof(PTE*) * num_pages);
    frame_table = (FTE*) malloc(sizeof(FTE*) * num_frames);
    page_table[0] = 5;
}



void process_inst(char * inst){
    int addr_offset = 2; //The addresses start at index 2 in the instruction string
    int virt_addr;

    if(inst[0] == 'W'){
        printf("BEGIN_WRITE\n");
        //TODO
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        printf("inst+2 %s", inst+addr_offset);
        printf("\t virt_addr=%d\n", virt_addr);
        printf("END_WRITE\n");
    }
    else if(inst[0] == 'R'){
        printf("BEGIN_READ\n");
        // TODO
        printf("END_READ\n");
    }
    else if(inst[1] == 'F'){
        printf("Print frame table\n");
        // TODO
    }
    else{
        printf("Print page table\n");
        // TODO
    }
}

void get_frame(int addr){

}
