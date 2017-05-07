#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vmm.h"
#include "queue.h"

//Tables
PTE *page_table;// = (PTE*) malloc(sizeof(PTE*) * num_pages);
FTE *frame_table;// = (FTE*) malloc(sizeof(FTE*) * num_frames);
int addr_size = 32; // num bits in virtual and phsyical addresses

struct queue *fifo_q;

int  virt_addr_num_page_bits;

// Defaults
int num_pages = 8;
int num_frames = 4;

int block_size = 1024;
char *rep_policy = "random";

/**
* Creates the page_table and frame_table of proper size.
* @param num_pages, the number of page table entries to allocate in the page_table.
* @param num_frames, the number of frame table entries to allocate in the frame_table.
*/
void create_tables(int num_pages, int num_frames){


    printf("******* IN CREATE *******\n");
    printf("num_pages: %d\n",num_pages);
    printf("num_frames: %d\n",num_frames);

    page_table = (PTE*) malloc(sizeof(PTE*) * num_pages);
    frame_table = (FTE*) malloc(sizeof(FTE*) * num_frames);

    fifo_q = newqueue();

    virt_addr_num_page_bits = 32 - ((int)(log(block_size) / log(2)));

    int i;
    // Set each frame to free (first bit set to 1)
    for(i = 0; i < num_frames; i++){
        frame_table[i] = 0x80000000;
    }
}



void process_inst(char * inst){

    srand(time(NULL));   //Set for random replacement policy

    int addr_offset = 2; //The addresses start at index 2 in the instruction string
    int virt_addr, page_num;

    if(inst[0] == 'W'){
        printf("BEGIN_WRITE\n");
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        
        printf("\tvirt_addr=0x%X\n", virt_addr);
        
        page_num = get_page_num(virt_addr);
        if(page_num < num_pages){
            
            get_phys_addr(page_num);
        }
        else{
            printf("\tSegmentation fault: illegal_page=%d\n", page_num);
        }

        printf("END_WRITE\n");
    }
    else if(inst[0] == 'R'){
        printf("BEGIN_READ\n");
        // TODO
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        
        printf("\tvirt_addr=0x%X\n", virt_addr);
        
        page_num = get_page_num(virt_addr);
        if(page_num < num_pages){
            
            get_phys_addr(page_num);
        }
        else{
            printf("\tSegmentation fault: illegal_page=%d\n", page_num);
        }

        printf("END_READ\n");
    }
    else if(inst[1] == 'F'){
        printf("Print frame table\n");
        print_frame_table();
    }
    else{
        printf("Print page table\n");
        print_page_table();
    }
}

/**
* Given a virtual address find the page number it corresponds to.
* @param virt_addr the virtual address in integer representation
* @return the page number for the address
*/ 
int get_page_num(int virt_addr){
    
    int page_num = virt_addr >> ((int)(log(block_size) / log(2)));
    return page_num;
}

void get_phys_addr(int page_num){

    if(page_table[page_num] >> 31 == 1){
        printf("\tPage is valid\n");
        // TODO get frame num and concatenate w/ offset
    }
    else{
        //TODO pull in page
        printf("\tPage fault: page=%d\n", page_num);
        allocate_frame(page_num);

    }
}

void allocate_frame(int page_num){

    int free_frame = -1;
    int i;
    //Go through the frames and look for a free one
    for(i = 0; i < num_frames; i++){
        
        // If this frame is free (F bit is set to 1)
        if((frame_table[i] & 0x80000000) == 0x80000000){
            free_frame = i;
            break;
        }

    }

    //No free frame was found so must run a replacement policy
    if(free_frame == -1){
        // TODO: run replacement policy
        free_frame = run_replacement_policy();
    }

    /** Update frame_table **/
    //Free bit needs to be 0 and page number needs to be set
    frame_table[free_frame] = page_num;

    /** Update page_table **/
    // Set frame number
    page_table[page_num] = free_frame;
    // Set valid and reference bit
    page_table[page_num] = page_table[page_num] | 0xA0000000;
}

int run_replacement_policy(){

    int free_frame; 
    // TODO: Complete
    if(strcmp(rep_policy, "random") == 0){

        free_frame = random_replacement();
    }
    if(strcmp(rep_policy, "fifo") == 0){

        free_frame = fifo_replacement();
    }


    /** Set old page table to invalid **/
    // Isolate page number by clearing out F bit
    // int old_page = frame_table[free_frame] << 1;
    // old_page = old_page >> 1;
    int old_page = frame_table[free_frame] & ~(1 << 31);

    page_table[old_page] = 0; //Page is now invalid

    return free_frame;
}

int fifo_replacement(){

    return 0;    
}

int random_replacement(){

    return rand() % num_frames;
}
void print_frame_table(){
    
    printf("Frame\t| F Page\n");

    int i;
    for(i = 0; i < num_frames; i++){

         //Print frame number
        printf("%d", i);

        //Print F bit
        int f = frame_table[i] >> 31;
        printf("\t| %d", f);

        //Print page number
        int page_num = frame_table[i]; //Get the whole entry
        //Clear out the F and unused bits to isolate the page number
        // TODO: Test, does this really work?
        page_num = page_num << (virt_addr_num_page_bits + 1);
        page_num = page_num >> (virt_addr_num_page_bits + 1);

        printf(" %d\n", page_num);
    }
}

void print_page_table(){

    int temp;

    printf("Page\t| V,M,R,Frame\n");

    int i;
    for(i = 0; i < num_pages; i++){

        // Page num
        printf("%d", i);

        // Valid bit
        printf("\t| %d,", page_table[i] >> 31);

        // Modified bit
        temp = page_table[i] & 0b01000000000000000000000000000000;
        printf("%d,", temp >> 30);

        // Referenced bit
        temp = page_table[i] & 0b00100000000000000000000000000000;
        printf("%d,", temp >> 29);

        // Frame number
        temp = page_table[i] & 0b00000011111111111111111111111111;
        printf("%d\n", temp);
    }
}