#ifndef __CSR__
#define __CSR__
#include <stdint.h>

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)    // MPP value for Machine mode
#define MSTATUS_MPP_S (1L << 11)    // MPP value for Supervisor mode
#define MSTATUS_MPP_U (0L << 11)    // MPP value for User mode
#define MSTATUS_MIE (1L << 3)       // machine-mode interrupt enable.

uint64_t r_sie();
void w_sie(uint64_t x);

uint64_t r_mhartid();

void w_satp(uint64_t x);
uint64_t r_satp();
void w_stvec(uint64_t x);
uint64_t r_stvec();

uint64_t r_scause();

uint64_t r_sepc();
void w_sepc(uint64_t x);

void w_mstatus(uint64_t x);
uint64_t r_mstatus();

uint64_t r_mtvec();
void w_mtvec(uint64_t x);

void w_medeleg(uint64_t x);
uint64_t r_medeleg();

void w_mideleg(uint64_t x);
uint64_t r_mideleg();

uint64_t r_mepc();
void w_mepc(uint64_t x);

#define SIE_SEIE (1L << 9) // external
#define SIE_STIE (1L << 5) // timer
#define SIE_SSIE (1L << 1) // software

#endif