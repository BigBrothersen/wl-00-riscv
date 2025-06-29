#ifndef __PROC__
#define __PROC__

#include <stdint.h>
#include "mem.h"

#define NPROC 32 // max number of process
void init_proctable();


enum procstate { NEW, READY, RUNNING, WAITING, END };

// struct trapframe {
//     // Registers to save for user context switching (if using user mode)
//     uint64_t ra;
//     uint64_t sp;
//     uint64_t gp;
//     uint64_t tp;
//     uint64_t t0, t1, t2;
//     uint64_t s0, s1;
//     uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
//     uint64_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
//     uint64_t t3, t4, t5, t6;
//     uint64_t epc;     // User program counter
// };

// struct context {
//     // Kernel context for scheduler context switch
//     uint64_t ra;
//     uint64_t sp;
//     uint64_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
// };

struct proc {
    int pid;
    enum procstate state;        // Process state
    char name[16]; // name of process

    pagetable_t pt; // page table of process
    uint64_t kstack;
    // struct trapframe *tf;

};


#endif