
#ifndef _MEMORY_H
#define _MEMORY_H

#include "types.h"
#include "functions.h"

#define fp_memcp8 fp_arm(0x20CE3E0, void, (void*, void*, u32))
static inline void memcp(void* dest, void* src, u32 size) { fp_memcp8(src, dest, size);}

#define fp_memset fp_arm(0x20CE34C, void, (void*, u8, u32))
static inline void memset(void* dest, u8 value, u32 size) { fp_memset(dest, value, size); }

static inline void write_u8(u8* address, u8 value) { *address = value; }
static inline void write_u16(u16* address, u16 value) { *address = value; }
static inline void write_u32(u32* address, u32 value) { *address = value; }

static inline void write_u32_16bit_alligned(u16* address, u32 value) {
    *address = value & 0xFFFF;
    address++;
    *address = value >> 0x10;
}

static inline u16 read_u16_unaligned(u16* addr) {
    u16 value;
    memcp(addr, &value, sizeof(u16));
    return value;
}

static inline u32 read_u32_unaligned(u32* addr) {
    u32 value;
    memcp(addr, &value, sizeof(u32));
    return value;
}

#define read_val(address, type) (*(type*) (address))
static inline u8 read_u8(u8* address) { return *address; }
static inline u16 read_u16(u16* address) { return *address; }
static inline u32 read_u32(u32* address) { return *address; }

static inline void write_u16_unaligned(u16* addr, u16 value) {
    memcp(&value, addr, sizeof(u16));
}

static inline void write_u32_unaligned(u32* addr, u32 value) {
    memcp(&value, addr, sizeof(u32));
}

#endif // _MEMORY_H
