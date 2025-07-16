#include <stdint.h>
#include "proc.h"
#include "defs.h"
#include "mem.h"

struct proc proctable[NPROC];
static int curr_pid = 0;
struct proc *initproc;

// initializes process table and define kernel memory region
void init_proctable() {
    struct proc *p;
    uintptr_t sp = (uintptr_t)(&end)-1;
    // printf("end %p kstack %p\n", sp, &kstack);
    for (p = proctable; p < &proctable[NPROC]; p++) {
        p->kstack = sp;
        p->state = UNUSED;   
        // printf("process %d kstack from %p to %p\n", i, (void*)sp, (void*)(sp - PAGE_SIZE + 1));
        sp = sp - PAGE_SIZE;
    }
}

pagetable_t init_userpt()
{
    pagetable_t pt;
    pt = (pagetable_t)ptcreate();
    if (pt == 0)
        return NULL;
    
    // TODO: mappages to trampoline
    
    
    return pt;
}
// TODO: find available space in process table returns the addess to that process table data
struct proc *procalloc() 
{
    struct proc *p;
    int found = 0;
    for (p = proctable; &proctable[NPROC]; p++) {
        if (p->state == UNUSED) {
            found = 1;
            break;
        }
    }
    if (!found)
        return NULL;

    p->state = NEW;
    p->pid = ++curr_pid;
    p->pt = init_userpt();
}

void init_userproc()
{
    struct proc *p;
    p = procalloc();
}

