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

//Replacement policy queues
struct queue *fifo_q;
struct queue *lru_q;

//Number of bits in virtual addr
int  virt_addr_num_page_bits;
int num_virt_offset_bits;

//Globals to keep track of instruction calls
int num_inst = 0;
int num_reads = 0;
int num_writes = 0;
int num_page_faults = 0;
int num_replacements = 0;

// Defaults
int num_pages = 8;
int num_frames = 3;
int block_size = 1024;
char *rep_policy = "fifo";

/**
* Creates the page_table and frame_table of proper size.
* @param num_pages, the number of page table entries to allocate in the page_table.
* @param num_frames, the number of frame table entries to allocate in the frame_table.
*/
void create_tables(int num_pages, int num_frames){

    srand(time(NULL));   //Set for random replacement policy

    page_table = (PTE*) malloc(sizeof(PTE*) * num_pages);
    frame_table = (FTE*) malloc(sizeof(FTE*) * num_frames);

    fifo_q = newqueue();
    lru_q = newqueue();

    num_virt_offset_bits = ((int)round((log(block_size) / log(2))));
    virt_addr_num_page_bits = 32 - num_virt_offset_bits;

    int i;
    // Set each frame to free (first bit set to 1)
    for(i = 0; i < num_frames; i++){
        frame_table[i] = 0x80000000;
    }
}



void process_inst(char * inst){


    int addr_offset = 2; //The addresses start at index 2 in the instruction string
    int virt_addr, page_num;

    if(inst[0] == 'W' || inst[0] == 'R'){

        num_inst++;

        char * read_or_write = (inst[0] == 'W') ? "WRITE" : "READ";
        printf("BEGIN %s\n", read_or_write);

        //Parese out the virtual addr
        virt_addr = (int)strtol(inst+addr_offset, NULL, 0);
        printf("\tvirt_addr=0x%X\n", virt_addr);
        
        //Get the page num from the virtual addr
        page_num = get_page_num(virt_addr);

        //Check if this is a valid page
        if(page_num < num_pages){
            
            //If so get the frame for this page
            int phys_addr;
            int frame = get_frame(page_num);

            // TODO: concatenate offset with frame
            phys_addr = frame; 
            phys_addr <<= num_virt_offset_bits;
            printf("\tphys_addr=0x%X\n", phys_addr);
        }
        else{
            printf("\tSegmentation fault: illegal_page=%d\n", page_num);
        }

        //If it is a write then the M (modified) bit needs to be set
        if(strcmp(read_or_write, "WRITE") == 0){

            page_table[page_num] |= 1 << 30;

            num_writes++;
        }
        else{

            num_reads++;
        }

        printf("END %s\n", read_or_write);

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
* Given a virtual address find the page number it corresponds to. This frees a frame if
* a free one can't be found. This also handles LRU and FIFO queue management
* @param virt_addr the virtual address in integer representation
* @return the page number for the address
*/ 
int get_page_num(int virt_addr){
    
    int page_num = virt_addr >> num_virt_offset_bits;
    return page_num;
}

int get_frame(int page_num){

    int frame;

    //If page_num is valid (in memory)
    if(page_table[page_num] >> 31 == 1){
        
        // Find the frame num for this page
        frame = page_table[page_num] & 0b00000011111111111111111111111111;

        remove_entry(frame, lru_q);

    }
    else{
       
        //Get a frame for this page
        printf("\tPage fault: page=%d\n", page_num);
        num_page_faults++;
        frame = allocate_frame(page_num);
        enqueue(frame, fifo_q);

    }

    //LRU queue
    enqueue(frame, lru_q);

    return frame;
}

int allocate_frame(int page_num){

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

    return free_frame;
}

int run_replacement_policy(){

    num_replacements++;
    
    int free_frame; 
    // TODO: Complete
    if(strcmp(rep_policy, "fifo") == 0){

        free_frame = fifo_replacement();
    }
    else if(strcmp(rep_policy, "lru") == 0){

        free_frame = lru_replacement();
    }
    // else if(strcmp(rep_policy, "clock") == 0){

    //     free_frame = clock_replacement
    // }
    else{

        free_frame = random_replacement();
    }

    /** Set old page table to invalid **/
    // Isolate page number by clearing out F (free) bit
    int old_page = frame_table[free_frame] & ~(1 << 31);

    //Check if M (modified) bit is set
    char *writeout = ((page_table[old_page] << 1)>> 31) ? "true" : "false";
    printf("\tPage replacement: evicted_page=%d (frame=%d), writeout=%s\n", old_page, free_frame, writeout);

    //Set page to invalid
    page_table[old_page] = 0; //Page is now invalid

    return free_frame;
}

int lru_replacement(){

    return dequeue(lru_q);
}

int fifo_replacement(){

    return dequeue(fifo_q);    
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
        int valid = page_table[i] >> 31;
        if(valid){

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
        else{
            printf("\t| 0,-,-,-\n");
        }
    }
}