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
int get_frame_num(int page_num);
void print_page_table(PTE * page_table);
