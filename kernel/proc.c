#include <stdint.h>
#include "proc.h"

struct proc proctable[NPROC];

// initializes process table
void init_proctable() {
    struct proc *p;
    for (p = proctable; p < &proctable[NPROC]; p++) {
        // printf("%d\n", i);
        // i++;
        p->state = WAITING;
    }
}