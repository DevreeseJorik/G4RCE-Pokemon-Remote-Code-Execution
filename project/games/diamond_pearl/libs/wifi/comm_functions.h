
#ifndef _COMMUNICATION_FUNCTIONS_H
#define _COMMUNICATION_FUNCTIONS_H

#include "util/functions.h"
#include "util/types.h"

#define COMM_STRUCT 0x02237CE0
typedef enum{
	SESSION_CANCEL,
	SESSION_ERROR,
	SESSION_START,
	SESSION_REQUEST,
	SESSION_GET_AUTH_TOKEN,
	SESSION_RECEIVED_AUTH_TOKEN,
	SESSION_UPLOAD,
	SESSION_COMPLETED
} COMMUNICATION_STATE;

#define fp_getResultState fp_thumb(0x022123A8, int, ())
static inline int getResultState() { return fp_getResultState(); }

#define fp_disconnect fp_thumb(0x0221244C, void, ())
static inline int disconnect() { fp_disconnect(); }

#define fp_asyncMainHandler fp_thumb(0x0222D5DC, void, ())
static inline void tryAsyncUpdate() { fp_asyncMainHandler(); }

#define fp_isAsyncComplete fp_thumb(0x0222DB98, BOOL, ())
static inline BOOL isAsyncComplete() { return fp_isAsyncComplete(); }

#define fp_getAsyncResult fp_thumb(0x0222DBB8, u32, ())
static inline u32 getAsyncResult() { return fp_getAsyncResult(); }

#define fp_fetchPokemonResult fp_thumb(0x0222DCB8, u32, (void*))
static inline u32 fetchPokemonResult(void* rcv_buf) { return fp_fetchPokemonResult(rcv_buf); }

#define fp_fetchPokemonResultWrapper fp_thumb(0x02234E68, u32, (void*))
static inline u32 fetchPokemonResultWrapper(void* rcv_buf) { return fp_fetchPokemonResultWrapper(rcv_buf); }

#define fp_parsePokemonResult fp_thumb(0x02234E7C, u32, (void*))
static inline u32 parsePokemonResult(void* rcv_buf) { return fp_parsePokemonResult(rcv_buf); }

#define fp_sendPokemonResult fp_thumb(0x0222DBC4, u32, (void*))
static inline u32 sendPokemonResult(void* send_buf) { return fp_sendPokemonResult(send_buf); }

#define fp_fetchPokemonSearchResult fp_thumb(0x0222DD90, u32, (void*, u32, void*))
static inline u32 fetchPokemonSearchResult(void* snd_buf, u32 rcv_count, void* rcv_buf) { return fp_fetchPokemonSearchResult(snd_buf, rcv_count, rcv_buf); }

#define fp_fetchPokemonSearchResultWrapper fp_thumb(0x2230DB8, u32, (void*))
static inline u32 fetchPokemonSearchResultWrapper(void* rcv_buf) { return fp_fetchPokemonSearchResultWrapper(rcv_buf); }

#endif // _COMMUNICATION_FUNCTIONS_H
