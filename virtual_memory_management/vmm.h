#include <stdint.h>

typedef uint32_t PTE;
typedef uint32_t FTE;

extern int num_pages;
extern int num_frames;
extern int block_size;
extern char *rep_policy;

extern int num_inst;
extern int num_reads;
extern int num_writes;
extern int num_page_faults;
extern int num_replacements;

void process_inst(char * inst);
void create_tables(int num_pages, int num_frames);
int get_page_num(int virt_addr);
int get_frame(int page_num);
int allocate_frame(int page_num);

/** Replacement policies **/
int run_replacement_policy();
int random_replacement();
int fifo_replacement();
int lru_replacement();

/** Printing **/
void print_frame_table();
void print_page_table();