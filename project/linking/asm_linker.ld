MEMORY {
    RAM : ORIGIN = 0x0, LENGTH = 60k
}

SECTIONS {
    . = 0x0;

    .text : {
        _start = 0x0;
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
