#include "graphics/poke_sprite.h"

__attribute__((naked))
__attribute__((section(".text.main")))
__attribute__((target("thumb")))
void main(void) {
    __asm__ volatile (
        "ldr r1,[r0,#0xc]\n"
        "ldr r0,[sp,#0x8]\n"
        "push {r0-r7, lr}\n"
    );
    CUSTOM_POKEMON* customPokemon = getCustomPokemon(SPRITE_INFO_ADDRESS);
    if (customPokemon != NULL) {
        __asm__ volatile (
            "mov r1, %0\n"
            "pop {r0}\n"
            "add sp, sp, #4\n"
            "pop {r2-r7, pc}\n"
            :
            : "r" (&customPokemon->palette)
        );
    }
    __asm__ volatile (
        "pop {r0-r7, pc}\n"
    );
}
