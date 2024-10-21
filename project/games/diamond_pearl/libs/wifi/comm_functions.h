
#ifndef _COMMUNICATION_FUNCTIONS_H
#define _COMMUNICATION_FUNCTIONS_H

#include "util/functions.h"
#include "util/types.h"

#define fp_asyncMainHandler fp_thumb(0x0222D5DC, void, ())
static inline void tryAsyncUpdate() { fp_asyncMainHandler(); }

#define fp_isAsyncComplete fp_thumb(0x0222DB98, BOOL, ())
static inline BOOL isAsyncComplete() { return fp_isAsyncComplete(); }

#define fp_getAsyncResult fp_thumb(0x0222DBB8, u32, ())
static inline u32 getAsyncResult() { return fp_getAsyncResult(); }

#define fp_fetchPokemonResult fp_thumb(0x02234E68, u32, (void*))
static inline u32 fetchPokemonResult(void* rcv_buf) { return fp_fetchPokemonResult(rcv_buf); }

#define fp_parsePokemonResult fp_thumb(0x02234E7C, u32, (void*))
static inline u32 parsePokemonResult(void* rcv_buf) { return fp_parsePokemonResult(rcv_buf); }

#define fp_sendPokemonResult fp_thumb(0x0222DBC4, u32, (void*))
static inline u32 sendPokemonResult(void* send_buf) { return fp_sendPokemonResult(send_buf); }

#endif // _COMMUNICATION_FUNCTIONS_H
