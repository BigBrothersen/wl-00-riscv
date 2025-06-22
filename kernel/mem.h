#ifndef __MEM__
#define __MEM__
#include <stdint.h>

#define MEM_START 0x80000000ULL
#define MEM_END (MEM_START + 128*1024*1024) // assume 128MB RAM
#define PAGE_SIZE 4096 // 4KB page
#define NUM_PAGES ((MEM_END-MEM_START)/PAGE_SIZE)

#define PGROUNDUP(sz)  (((sz)+PAGE_SIZE-1) & ~(PAGE_SIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PAGE_SIZE-1))

void print_mem(uint32_t addr, int len, int increment);
void bitmap_init();
void kfree_range(void *start_pa, void *end_pa);
void *kalloc();
void kfree(void *pa);
void *memset(void *ptr, int value, uint32_t num);
int page_idx(void *pa);

#endif