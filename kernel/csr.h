#ifndef __CSR__
#define __CSR__
#include <stdint.h>

uint64_t r_mhartid();

void w_satp(uint64_t x);
uint64_t r_satp();
void w_stvec(uint64_t x);
uint64_t r_stvec();

uint64_t r_scause();

uint64_t r_sepc();

uint64_t r_mstatus();

uint64_t r_mtvec();
void w_mtvec(uint64_t x);

void w_medeleg(uint64_t x);
void w_mideleg(uint64_t x);

#endif