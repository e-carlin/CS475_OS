#include <stdint.h>

typedef uint32_t PTE;
typedef uint32_t FTE;

extern int num_pages;
extern int num_frames;
extern int block_size;
extern char *rep_policy;

void process_inst(char * inst);
void create_tables(int num_pages, int num_frames);
int get_page_num(int virt_addr);
void get_phys_addr(int page_num);
void allocate_frame(int page_num);

/** Replacement policies **/
int run_replacement_policy();
int random_replacement();
int fifo_replacement();

/** Printing **/
void print_frame_table();
void print_page_table();