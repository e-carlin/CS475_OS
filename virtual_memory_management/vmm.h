#include <stdint.h>

typedef uint32_t PTE;
typedef uint32_t FTE;

void process_inst(char * inst);
void create_tables(int num_pages, int num_frames);