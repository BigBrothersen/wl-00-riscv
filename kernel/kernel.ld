/* MEMORY STRUCTURE:
|   stack   |
|     ↓     |
|     ↑     |
|   heap    |
|    bss    |
|   data    |
|   text    |

ALIGN(16) -> align address to the multiple of 16 (0x10)
*/

ENTRY(_entry)
SECTIONS
{
    . = 0x80000000;

    _stext = .;
    .text : {
        *(.text .text.*)
        . = ALIGN(0x1000);
    }
    _etext = .;
    . = . + 0x1000;
    _sdata = .;
    .data : {
        *(.data .data.*)
        . = ALIGN(0x1000);
    }
    _edata = .;
    . = . + 0x1000;
    _sbss = .;
    .bss : {
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(0x1000);
    }
    _ebss = .;
    . = . + 0x1000;
 
    . = ALIGN(0x1000);
    . = . + 0x1000;
    m_stack_end = .;
    . = ALIGN(0x1000);
    . = . + 0x1000;
    s_stack_end = .;
    . = . + 0x20000; /* 128KB kernel stack (32 processes) */

    PROVIDE(end = .);
}

