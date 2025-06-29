#include <stdint.h>

// which cpu this thread runs on
uint64_t r_mhartid()
{
    uint64_t x;
    asm volatile("csrr %0, mhartid" : "=r" (x) );
    return x;
}

// address translation/mmu control
void w_satp(uint64_t x)
{
    asm volatile("csrw satp, %0" : : "r" (x));
}

uint64_t r_satp() {
    uint64_t x;
    asm volatile("csrr %0, satp" : "=r"(x));
    return x;
}

// supervisor trap Cause
uint64_t r_scause()
{
  uint64_t x;
  asm volatile("csrr %0, scause" : "=r" (x) );
  return x;
}

//
uint64_t r_sepc()
{
    uint64_t x;
    asm volatile("csrr %0, sepc" : "=r" (x) );
    return x;
}

uint64_t r_mstatus() {
    uint64_t x;
    asm volatile("csrr %0, mstatus" : "=r"(x));
    return x;
}

// supervisor trap vector
uint64_t r_stvec() {
    uint64_t x;
    asm volatile("csrr %0, stvec" : "=r"(x));
    return x;
}

void w_stvec(uint64_t x) 
{
    x = x & ~0x3;
    // printf("fuck you %p\n", x);
    asm volatile("csrw stvec, %0" : : "r"(x));
}

uint64_t r_mideleg()
{
  uint64_t x;
  asm volatile("csrr %0, mideleg" : "=r" (x) );
  return x;
}

void w_mideleg(uint64_t x)
{
  asm volatile("csrw mideleg, %0" : : "r" (x));
}

uint64_t r_medeleg()
{
  uint64_t x;
  asm volatile("csrr %0, medeleg" : "=r" (x) );
  return x;
}

void w_medeleg(uint64_t x)
{
  asm volatile("csrw medeleg, %0" : : "r" (x));
}

uint64_t r_mtvec() 
{
    uint64_t x;
    asm volatile("csrr %0, mtvec" : "=r"(x));
    return x;
}

void w_mtvec(uint64_t x) {
    x = x & ~0x3;
    asm volatile("csrw mtvec, %0" : : "r" (x));
}