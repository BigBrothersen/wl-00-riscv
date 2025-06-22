#include <stdint.h>
#include "print.h"
// Kernel file for memory management
// Allocates physical memory
#define MEM_START 0x80000000
#define MEM_END 0X8800000 // assume 128MB RAM
#define PAGE_SIZE 4096
#define NUM_PAGES ((MEM_START-MEM_END)/PAGE_SIZE)

//Bitmap of available physical memories in form of pages. 1 is available, 0 is occupied page.
static uint8_t mem_bitmap[NUM_PAGES];

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

// TODO: Create a function to initialize the mapping from non-kernel pages up to end of physical memory
void bitmap_init(){

}


// TODO: function to fill block of memory with certain values
void *memset(void *ptr, int value, uint32_t num) {
    
}

// TODO: Function to free the physical memory pointed by the page address
void kfree(void *pa){

}

// TODO: Function that allocates a single page of physical memory. Returns a pointer pointing to the page. If fails return null pointer.
void *kalloc(){

}