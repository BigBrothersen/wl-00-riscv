#include "print.h"
#include "uart.h"
#include "mem.h"
#include "defs.h"



void main() {
    // uart_init(); // UART is configured by default by QEMU
    printf("\n");
    printf("wl-00 kernel is booting");
    printf("\n");

    init_bitmap();  // allocate memory for bitmap
    init_kptable(); // initialize kernel page table   
    // printf("paging status %d\n", paging_status());
    init_kvmhart(); // enable paging
    // printf("paging status %d\n", paging_status());
    while(1);
}