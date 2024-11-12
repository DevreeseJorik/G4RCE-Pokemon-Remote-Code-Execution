#include "util/types.h"

__attribute__((naked))
__attribute__((section(".text.main")))
__attribute__((target("thumb")))
void main(void) {
    __asm__ volatile (
        "push {r1-r7, lr}\n"
    );
    *(u8*) 0x206B2FE = 0x8;
    __asm__ volatile (
        "mov r0, #0x1\n"
        "pop {r1-r7, pc}\n"
    );
}
