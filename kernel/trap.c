#include <stdint.h>
#include "csr.h"
#include "print.h"

extern void kerneltrap(); // kerneltrap.S
void main();

void init_trap() 
{
    w_stvec((uintptr_t)kerneltrap);
}

// machine mode trap_handle
void m_trap_handle(uint64_t mcause, uint64_t mepc, uint64_t mval) {
    printf("TRAP: mcause = 0x%p, mepc = 0x%p, mval = 0x%p\n", mcause, mepc, mval);
    switch (mcause) {
        case 0x8: // user mode ecall
            break;
        case 0x9: // supervisor mode ecall
            break;
        case 0xb: {// machine mode ecall
            printf("Detected ecall from m-mode\n");
            w_mepc(mepc+4);
            printf("mepc %p\n", r_mepc());
            break;
        }
        default:
            printf("Unknown syscall");
    }
}


void s_trap_handle(uint64_t scause, uint64_t sepc) {
    printf("TRAP: scause = 0x%p, sepc = 0x%p\n", scause, sepc);
    switch (scause) {
        case 0x8: // user mode ecall
            break;
        case 0x9: // supervisor mode ecall
            break;
        case 0xb: {// machine mode ecall
            printf("Detected ecall from m-mode\n");
            w_sepc(sepc+4);
            printf("mepc %p\n", r_mepc());
            break;
        }
        default:
            printf("Unknown syscall");
    }
}
