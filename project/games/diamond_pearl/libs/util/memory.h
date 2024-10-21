
#ifndef _MEMORY_H
#define _MEMORY_H

#include "types.h"
#include "functions.h"

#define fp_memcp8 fp_arm(0x20CE3E0, void, (void*, void*, u32))
static inline void memcp(void* dest, void* src, u32 size) { fp_memcp8(dest, src, size);}

#define fp_memset fp_arm(0x20CE34C, void, (void*, u8, u32))
static inline void memset(void* dest, u8 value, u32 size) { fp_memset(dest, value, size); }

#endif // _MEMORY_H
