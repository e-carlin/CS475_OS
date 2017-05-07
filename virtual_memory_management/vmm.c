#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vmm.h"

//Tables
PTE *page_table;// = (PTE*) malloc(sizeof(PTE*) * num_pages);
FTE *frame_table;// = (FTE*) malloc(sizeof(FTE*) * num_frames);
int addr_size = 32; // num bits in virtual and phsyical addresses

// Defaults
int num_pages = 8;
int num_page_bits;

int num_frames = 4;

int block_size = 1024;
char *rep_policy = "random";

/**
* Creates the page_table and frame_table of proper size.
* @param num_pages, the number of page table entries to allocate in the page_table.
* @param num_frames, the number of frame table entries to allocate in the frame_table.
*/
void create_tables(int num_pages, int num_frames){

    num_page_bits  = (int)(log(num_pages) / log(2));

    printf("******* IN CREATE *******\n");
    printf("num_pages: %d\n",num_pages);
    printf("num_page_bits: %d\n",num_page_bits);
    printf("num_frames: %d\n",num_frames);

    page_table = (PTE*) malloc(sizeof(PTE*) * num_pages);
    frame_table = (FTE*) malloc(sizeof(FTE*) * num_frames);

    int i;
    // Set each frame to free (first bit set to 1)
    for(i = 0; i < num_frmaes; i++){
        frame_table[i] = 0x80000000;
    }
}



void process_inst(char * inst){
    int addr_offset = 2; //The addresses start at index 2 in the instruction string
    int virt_addr, page_num;

    if(inst[0] == 'W'){
        printf("BEGIN_WRITE\n");
        //TODO
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        printf("\tvirt_addr=%d\n", virt_addr);
        printf("\tPage: %d\n", get_page_num(virt_addr));
        page_num = get_page_num(virt_addr);
        get_phys_addr(page_num);

        printf("END_WRITE\n");
    }
    else if(inst[0] == 'R'){
        printf("BEGIN_READ\n");
        // TODO
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        printf("\tvirt_addr=%d\n", virt_addr);
        printf("\tPage: %d\n", get_page_num(virt_addr));
        page_num = get_page_num(virt_addr);
        get_phys_addr(page_num);
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

/**
* Given a virtual address find the page number it corresponds to.
* @param virt_add the virtual address
* @return the page number for the address
*/ 
int get_page_num(int virt_addr){
    
    int page_num = virt_addr >> ((int)(log(block_size*8) / log(2)) - num_page_bits);
    return page_num;
}

void get_phys_addr(int page_num){

    if(page_table[page_num] >> 31 == 1){
        printf("\tPage is valid\n");
        // TODO get frame num and concatenate w/ offset
    }
    else{
        printf("\tPage is INvalid\n");
        //TODO pull in page
        int frame_num = get_frame_num(page_num);

    }
}

int get_frame_num(int page_num){
    // TODO

    return -1;
}


void print_page_table(PTE * page_table){
    
}