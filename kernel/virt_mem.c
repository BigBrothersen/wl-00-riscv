#include <stdint.h>
#include "print.h"
#include "defs.h"
#include "uart.h"
#include "mem.h"
#include "csr.h"

/*
Each process will have its own page table (an array of pointers where each pointer points to a direct page within the physical memory or frame)
VA	Purpose	PA
0x00001000	User stack	0x80400000
0x80000000	Kernel text	0x80000000
0x10000000	UART MMIO	0x10000000

sv32
| 31........22 | 21........12 | 11........0 |
|   VPN[1]     |   VPN[0]     | page offset |
*/

void init_kptable() 
{
    kptable = kptable_make();
}

// void init_uptable()
// {
//     uptable = uptable_make();
// }

// pagetable_t uptable_make()
// {
//     pagetable_t upt;
//     upt = (pagetable_t)kalloc();
//     memset(upt, 0, PAGE_SIZE);
//     return upt;
// }

// allocates memory, virtual memory map, and returns kernel pagetable
pagetable_t kptable_make() 
{
    pagetable_t kpt;
    kpt = (pagetable_t)kalloc();
    memset(kpt, 0, PAGE_SIZE);

    // initialize UART
    mappages(kpt, UART_0, UART_0, PAGE_SIZE, PTE_R | PTE_W);
    
    // // map kernel text (read only)
    mappages(kpt, KERNBASE, KERNBASE, (uintptr_t)(&_etext), PTE_R);

    // // map the rest 
    mappages(kpt, (uint32_t)&_etext, (uint32_t)&_etext, MEM_END-(uintptr_t)(&_etext), PTE_R | PTE_W);

    return kpt;
}

// since the kernel processes have one-to-one correspondence, no need for complex translation
int mappages(pagetable_t pt, uint32_t va, uint32_t pa, uint32_t size, int flags) {
    if ((va % PAGE_SIZE) != 0){
        error("mappages: va not aligned");
        return 0;
    }
    if ((pa % PAGE_SIZE) != 0) {
        error("mappages: pa not aligned");
        return 0;
    }
    if ((size % PAGE_SIZE) != 0) {
        error("mappages: size not aligned");
        return 0;
    }
    if (size == 0) {
        error("mappages: size 0");
        return 0;
    }

    // Calculate mapping boundaries
    uintptr_t end = va + size;
    pte_t *pte;
    int ret = 0;

    // Map each page in the range
    for (uintptr_t curr_va = va; curr_va < end; curr_va += PAGE_SIZE, pa += PAGE_SIZE) {
        pte = mappage(pt, curr_va, pa, flags);
        if (!pte) {
            error("mappages: failed to map va to pa");
            ret = -1;
            break;
        }
        // Debug output
        // printf("Mapped VA %p -> PA %p (PTE @ %p, value %p)\n", curr_va, pa, pte, *pte);
    }
    return ret;
}

pte_t *mappage(pagetable_t pt, uint32_t va, uint32_t pa, int flags) 
{
    if ((va % PAGE_SIZE) != 0)
        error("mappage: va not aligned");
    if ((pa % PAGE_SIZE) != 0)
        error("mappage: pa not aligned");

    uint32_t vpn1 = (va >> 22) & 0x3ff; // shift 22 bits to right
    uint32_t vpn0 = (va >> 12) & 0x3ff; // shift 12 bits to the right

    //printf("Map VA %p (VPN1=%u, VPN0=%u) -> PA %p\n", va, vpn1, vpn0, pa);
    //printf("PD %p[%u] = %p (current)\n", pt, vpn1, pt[vpn1]);
    if ((pt[vpn1] & PTE_V) == 0) {
        // Create a second level page table
        pte_t pt_addr = (pte_t)kalloc();   // allocate new page for second level page table
        //printf("  Allocated L2 PT at PA %p\n", pt_addr);
        pt[vpn1] = ((pt_addr / PAGE_SIZE) << 10) | PTE_V; // Set the (Page Physical Number) and valid bit
        //printf("  Updated PD %p[%u] = %p (PPN=%u | V)\n", pt, vpn1, pt[vpn1], (pt_addr / PAGE_SIZE));
    }

    pte_t *table = (uint32_t*)((pt[vpn1] >> 10)*PAGE_SIZE);
    //printf("PT %p[%u] = %p (before)\n", pt, vpn0, table[vpn0]);

    table[vpn0] = ((pa/PAGE_SIZE) << 10) | flags | PTE_V;
    //printf("  Updated PT %p[%u] = %p (PPN=%u | %s | V)\n", table, vpn0, table[vpn0], (pa / PAGE_SIZE), (flags & PTE_W) ? "RW" : "R");
    //printf("Mapped VA %p -> PA %p (flags=0x%x)\n\n", va, pa, flags);
    // if ((void*)&table[vpn0] == (void*)NULL) {
    //     return NULL;
    // }
    //printf("address lol %p pa %p\n", &table[vpn0], PTE2PA(&table[vpn0]));
    return &table[vpn0];
}

void init_kvmhart()
{
    uintptr_t root_pa = (uintptr_t)kptable;
    uint32_t root_ppn = root_pa >> 12;
    uint32_t satp_val = (1 << 31) | root_ppn;       
    w_satp(satp_val);                             
    __asm__ volatile("sfence.vma zero, zero");
}

int paging_status() {
    uint64_t x = r_satp();
    return (x >> 31) & 1;
}

pagetable_t ptcreate() {
    pagetable_t pt;
    pt = (pagetable_t)kalloc();
    if (pt == NULL)
        return 0;
    memset(pt, 0, PAGE_SIZE);
    return pt;
}

// void init_trap() 
// {
//     // asm volatile("csrw stvec, %0" :: "r"(kerneltrap));
//     // printf("stvec %p\n", r_stvec());
//     // printf("kernel trap %p\n", kerneltrap);
//     uintptr_t tepp = kerneltrap;
//     w_stvec(tepp);
//     // printf("stvec %p\n", r_stvec());
// }