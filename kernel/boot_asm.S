# load kernel into 0x80000000
.section .text
.global _entry
_entry:
    # stack size = 4096B
    la sp, kstack   # load stack pointer with stack0 or 0x8000000
    li t0, 1024*4   # store another stack
    add sp, sp, t0  # new stack
    call boot       # jump to boot.c

loop:
    j loop

