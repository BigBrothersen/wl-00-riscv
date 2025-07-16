#include "csr.h"
#include "print.h"
#include "trap.h"

extern void _main(); // boot asm
void main(void);

void boot()
{
    uint64_t mstatus = r_mstatus();
    mstatus &= ~MSTATUS_MPP_MASK;           // clear MPP (bits 12:11)
    mstatus |=  MSTATUS_MPP_S;
    w_mstatus(mstatus);
    w_mideleg(0xffff);
    w_medeleg(0xffff);
    uint64_t sie = r_sie();
    w_sie(sie | SIE_SEIE | SIE_STIE | SIE_SSIE);
    w_mepc((uintptr_t)_main);
    asm volatile("mret");
}