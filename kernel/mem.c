#include <stdint.h>
#include "print.h"
#include "defs.h"
#include "mem.h"
// Kernel file for memory management
// Allocates physical memory

//Bitmap of available physical memories in form of pages. 1 is available, 0 is occupied page.
static uint8_t mem_bitmap[NUM_PAGES];
static char *start_page = &end;

// TODO: completed but need refining, debugging tool
void print_mem(uint32_t addr, int len, int increment)
{
    if (!(increment == 1 || increment == 2 || increment == 4 || increment == 8)){
        printf("Invalid increment");
        return;
    }

    uint8_t *ptr = (uint8_t *) addr;
    int i;
    for (i = 0; i < len; i += increment) {
        void *curr_addr = (void *)(ptr+i);
        printf("%p: ", curr_addr);

        switch (increment){
            case 1: {
                uint8_t *val = (uint8_t *)curr_addr; // 1 byte
                printf("%x\n", *val);
                break;
            }
            case 2: {
                uint16_t *val = (uint16_t *)curr_addr; // 1 byte
                printf("%x\n", *val);
                break;
            }
            case 4: {
                uint32_t *val = (uint32_t *)curr_addr; // 1 byte
                printf("%x\n", *val);
                break;
            }
            case 8: {
                uint64_t *val = (uint64_t *)curr_addr; // 1 byte
                printf("%x\n", *val);
                break;
            }
        }
    }
}

// void debug_bitmap() {
//     for (int i = 0; i < 20; i++) {
//         printf("page %d: %d\n", i, mem_bitmap[i]);
//     }
// }

// TODO: Create a function to initialize the mapping from non-kernel pages up to end of physical memory
void bitmap_init(){
    // printf("end address is %p and the round up is %p\n", start_page, (void*)PGROUNDUP((uintptr_t)MEM_END));
    int i;
    // set kernel region as occupied
    // printf("start page %p %d\n", start_page, page_idx(start_page));
    for (i = 0; i < page_idx(start_page); i++) {
        // printf("%d\n", i);
        mem_bitmap[i] = 0;
    }
    kfree_range(start_page, (void *)MEM_END);
    // debug_bitmap();
}

// Free all pages from start_pa to end_pa
void kfree_range(void *start_pa, void *end_pa){
    if (start_pa >= end_pa) return;
    char *curr = (char *)PGROUNDUP((uintptr_t)start_pa);
    char *end = (char *)PGROUNDDOWN((uintptr_t)end_pa);
    do {
        kfree(curr);
        curr += PAGE_SIZE;
    } while (curr < (char *)end);
}

int page_idx(void *pa) {
    char *addr = (char *)PGROUNDDOWN((uintptr_t)pa);
    int idx;
    idx = ((addr - (char *)MEM_START)/PAGE_SIZE);
    return idx;
}

// TODO: function to fill block of memory with certain values
void *memset(void *ptr, int value, uint32_t num) {
    char *curr = (char *)ptr;
    int i;
    for (i = 0; i < num; i++, curr += 1) {
        *curr = value;
    }
    return (char *)ptr;
}

// TODO: Function to free the physical memory pointed by the page address
void kfree(void *pa){
    // memset(pa, 0, PAGE_SIZE); // optional for memory security, adds additional overhead;
    int i = page_idx(pa);
    mem_bitmap[i] = 1;
}


// TODO: Function that allocates a single page of physical memory. Returns a pointer pointing to the page. If fails return null pointer.
void *kalloc(){
    char *addr;
    for (int i = 0; i < NUM_PAGES; i++) {
        if (mem_bitmap[i]) {
            mem_bitmap[i] = 0;
            addr = (MEM_START + i*PAGE_SIZE);
            printf("allocated page %d %d with address %p", i, page_idx(addr), addr);
            return addr;
        }
    }
    return NULL;
}