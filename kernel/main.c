#include "print.h"
#include "uart.h"
#include "mem.h"
#include "defs.h"



void main() {
    // uart_init(); // UART is configured by default by QEMU
    printf("\n");
    printf("wl-00 kernel is booting");
    printf("\n");

    // printf("%p\n", MEM_START);
    // printf("%p\n", MEM_END);
    // printf("%d\n", NUM_PAGES);

    // // printf("text start: %p\n", &_stext);
    // // printf("text end: %p\n", &_etext);
    // // printf("data start: %p\n", &_sdata);
    // // printf("data end: %p\n", &_edata);
    // // printf("bss start: %p\n", &_sbss);
    // // printf("bss end: %p\n", &_ebss);
    // // printf("kstack: %p\n", &kstack);
    // printf("end: %p\n", &end);

    // printf("Hex value: 0x%x\n", 256);
    // int *ptr = MEM_START + 0x0001000;
    // printf("Value of each bytes:\n");
    // print_mem(ptr, 32, 1);
    while(1);
}