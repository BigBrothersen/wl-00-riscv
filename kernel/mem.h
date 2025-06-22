#ifndef __MEM__
#define __MEM__
#include <stdint.h>

#define MEM_START 0x80000000ULL
#define MEM_END (MEM_START + 128*1024*1024) // assume 128MB RAM
#define PAGE_SIZE 4096 // 4KB page
#define NUM_PAGES ((MEM_END-MEM_START)/PAGE_SIZE)

#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

void print_mem(uint32_t *addr, uint32_t len, uint32_t increment);


#endif