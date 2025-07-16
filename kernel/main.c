#include "print.h"
#include "uart.h"
#include "mem.h"
#include "defs.h"

#include "csr.h"
#include "trap.h"
#include "proc.c"

void main() {
    // uart_init(); // UART is configured by default by QEMU
    printf("\n");
    printf("wl-00 kernel is booting");
    printf("\n");
    init_bitmap();  // allocate memory for bitmap
    init_kptable(); // initialize kernel page table   
    init_kvmhart(); // enable paging
    init_trap();    // initialize trap vector
    init_proctable(); // initialize process table
    
    asm volatile("ecall"); // use this to trigger trap handler
    // TODO: implement syscall
    // implement trap handler
    // init_userprocess(); // TODO: implement first user process (shell)
    while(1);
}
