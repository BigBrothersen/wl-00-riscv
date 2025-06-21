ENTRY(_entry)

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text)
    }

    .bss : {
        *(.bss)
    }

    . = . + 0x1000;
    stack0 = .;
}