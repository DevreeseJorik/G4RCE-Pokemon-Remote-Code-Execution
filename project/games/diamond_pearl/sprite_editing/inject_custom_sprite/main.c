#include "graphics/poke_sprite.h"

__attribute__((naked))
__attribute__((section(".text.main")))
__attribute__((target("thumb")))
void main(void) {
    __asm__ volatile (
        "push {r0-r7, lr}\n"
    );
    loadOrInjectSprite();
    __asm__ volatile (
        "pop {r0-r7, pc}\n"
    );
}
