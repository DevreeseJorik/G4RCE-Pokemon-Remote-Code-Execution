#ifndef _DEBUGGING_H
#define _DEBUGGING_H

#include "util/types.h"
#include "util/functions.h"
#include "util/memory.h"
#include <stdint.h>

static u8 command_data[40] __attribute__((section(".data.command_data"))) = {
    0x00, 0x00, 0x00, 0x00, // padding
    0xBD, 0x00, 0xB2, 0x02, 0xB3, 0x00, 0x0C, 0x80, 0x29, 0x00,
    0x04, 0x80, 0x0C, 0x80, 0xB2, 0x00, 0x04, 0x80, 0x0C, 0x80,
    0xA1, 0x00, 0xBC, 0x00, 0x06, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x00, 0x00, 0xBD, 0x00, 0x02, 0x00
};

void setDotArtistToGTSProc() {
    u32 base_address = 0x02106FC0;
    u32* base_pointer = (u32*)(*(u32*)base_address);
    u32* dot_artist = (u32*)((u8*)base_pointer + 0x138A);

    // set command pointer to command data
    void* command_pointer;
    __asm__ volatile (
        "mov %0, pc\n"
        "add %0, #0x18\n"
        : "=r" (command_pointer)
        : "r" (&command_data)
        : "memory"
    );

    memcp(command_pointer, dot_artist, sizeof(command_data) + 10);
}

#endif // _DEBUGGING_H
