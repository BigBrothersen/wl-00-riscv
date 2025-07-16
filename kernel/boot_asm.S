# boot.S
.section .text.init
.global _entry
_entry:
    la sp, m_stack_end
    andi sp, sp, -16
    la t0, m_trap_handle
    csrw mtvec, t0
    call boot
    j .

.section .text
.global _main
_main:
    la sp, s_stack_end
    andi sp, sp, -16
    la t0, s_trap_handle
    csrw stvec, t0
    call main
    j .