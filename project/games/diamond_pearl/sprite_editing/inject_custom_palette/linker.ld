MEMORY {
    RAM : ORIGIN = 0x023AA980, LENGTH = 60k
}

SECTIONS {
    .text : {
        _start = 0x023AA900;
        KEEP(*(.text.main))
        KEEP(*(.text.main_thumb))
        *(.text.startup)
        *(.text*)
        . = ALIGN(4);
    } > RAM

    .rodata : {
        *(.rodata*)
        . = ALIGN(4);
    } > RAM

    .data : {
        *(.data*)
        . = ALIGN(4);
    } > RAM

    .got : {
        *(.got*)
        . = ALIGN(4);
    } > RAM
}
