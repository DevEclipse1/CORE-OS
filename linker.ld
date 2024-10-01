ENTRY(boot)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    . = 0x00100000;
    
    /* Multiboot header must be placed at the very beginning */
    .multiboot :
    {
        *(.multiboot)
    }

    .text :
    {
        *(.text*)
        *(.rodata*)
    }

    .data :
    {
        start_ctors = .;
        KEEP(*(.init_array));
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
        end_ctors = .;
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }

    /DISCARD/ :
    {
        *(.fini_array*)
        *(.comment)
    }
}
