.section .text
.global kerneltrap
.align 4
kerneltrap:
    csrr a0, mcause
    csrr a1, mepc
    csrr a2, mtval
    la t2, trap_handle
    jr t2
# kerneltrap is for machine mode, will implement s-mode later