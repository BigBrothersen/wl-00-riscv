#ifndef __MEM__
#define __MEM__
#include <stdint.h>

#define MEM_START 0x80000000ULL
#define KERNBASE 0x80000000ULL
#define MEM_END 0x88000000ULL
// #define MEM_END   (KERNBASE + (128*1024*1024)ULL)  // 128MB RAM (0x88000000)
#define PAGE_SIZE 4096 // 4KB page
#define PAGE_SHIFT 12    // number of bits needed to change to next page 
#define PAGE_SIZE_HEX 0x1000
#define NUM_PAGES ((MEM_END-MEM_START)/PAGE_SIZE)

#define PGROUNDUP(sz)  (((sz)+PAGE_SIZE-1) & ~(PAGE_SIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PAGE_SIZE-1))


void print_mem(uint32_t addr, int len, int increment);
void init_bitmap();
void kfree_range(void *start_pa, void *end_pa);
void *kalloc();
void kfree(void *pa);
void *memset(void *ptr, int value, uint32_t num);
int page_idx(void *pa);
uint8_t page_empty(int i);


// virtual memory virt_mem.c

// Virtual memory definitions 
typedef uint32_t pte_t;
typedef pte_t* pagetable_t;
#define PTE_V (1ULL << 0) // Valid
#define PTE_R (1ULL << 1) // Readable
#define PTE_W (1ULL << 2) // Writable


#define RAM_SIZE      (128 * 1024 * 1024)  // 128MB RAM
#define MINKVA        KERNBASE
#define MAXKVA        (MINKVA + RAM_SIZE - 1)
#define MINVA         0x10000   // 0x0000 - 0xffff is reserved
#define MAXVA         (MINVA + RAM_SIZE - 1) // Max virtual address (0x07FFFFFF)
#define NUM_PTES      (RAM_SIZE / PAGE_SIZE)  // 32,768 PTEs (128MB / 4KB)


#define PTE2PA(pte) ((*(uint32_t*)(pte) >> 10) << 12)
#define PA2PTE(pa) ((*((uint64 *)pa) >> 12) << 10)

/*
// Max Virtual Address (exclusive upper bound)
// For a 32-bit address space, the addresses range from 0x00000000 to 0xFFFFFFFF.
// The total size of the address space is 2^32 bytes.
#define VIRTUAL_ADDRESS_BITS 32
#define MAX_VA_SIZE_BYTES    (1UL << VIRTUAL_ADDRESS_BITS) // 4 GB
#define MAX_VA_ADDR          (MAX_VA_SIZE_BYTES - 1)       // 0xFFFFFFFF
*/

// page directory for kernel processes
static pagetable_t kptable;

// user page table;

void init_kptable();
pagetable_t kptable_make();
void *get_pa(void *va);
pte_t *mappage(pagetable_t pt, uint32_t va, uint32_t pa, int flags);
int mappages(pagetable_t pt, uint32_t va, uint32_t pa, uint32_t size, int flags);
int paging_status();
void init_kvmhart();
pagetable_t ptcreate();

#endif;