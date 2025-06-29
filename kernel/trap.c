#include <stdint.h>
#include "csr.h"
#include "print.h"

extern void kerneltrap(); // kerneltrap.S

void init_trap() 
{
    // w_stvec((uintptr_t)kerneltrap);
    w_mtvec((uintptr_t)kerneltrap);
}

// machine mode trap_handle
// TODO: decide what to do with each error/interrupt, refer to documentation for handling each error
void trap_handle(uint64_t mcause, uint64_t mepc, uint64_t mval) {
    printf("TRAP: mcause = 0x%p, mepc = 0x%p, mval = 0x%p\n", mcause, mepc, mval);
}



// TODO: implement S-mode trap_handle