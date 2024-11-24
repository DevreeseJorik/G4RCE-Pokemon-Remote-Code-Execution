#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "comm_functions.h"
#include "packets.h"

#include "util/types.h"

#define SND_PACKET_BUFF_ADDRESS (PACKET *) 0x02000000
#define RCV_PACKET_BUFF_ADDRESS (PACKET *) 0x023B0000

#define PACKET_COUNT 7

static inline void fetchPacket(PACKET *packet, u32 packet_count) { fetchPokemonSearchResult((void *) SND_PACKET_BUFF_ADDRESS, packet_count, packet); }
static inline void sendPacket(PACKET *packet) { sendPokemonResult(packet); }
static inline u32 downloadPacket(PACKET *packet, u32 packet_count);
static inline u32 uploadPacket(PACKET *packet);
static inline u32 handleAsync();

void handlePackets();
BOOL handlePacket(PACKET *packet);
BOOL handleDataPacket(DATA_PACKET *packet);
BOOL handleCodePacket(CODE_PACKET *packet);
BOOL handleDumpPacket(DUMP_PACKET *packet);

#endif // _COMMUNICATION_H
