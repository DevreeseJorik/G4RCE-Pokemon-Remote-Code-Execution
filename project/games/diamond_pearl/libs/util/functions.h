#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdint.h>

#define fp_arm(address, type, param) ((type (*) param)((uintptr_t)(address) & ~1))
#define fp_thumb(address, type, param) ((type (*) param)((uintptr_t)(address) | 1))

#endif // _FUNCTIONS_H
