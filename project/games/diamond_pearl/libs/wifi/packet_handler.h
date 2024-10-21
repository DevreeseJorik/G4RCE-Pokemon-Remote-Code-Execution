#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "comm_functions.h"
#include "packets.h"

#include "util/types.h"

#define RCV_PACKET_BUFF_ADDRESS (HTTP_PACKET *) 0x23B0000

static inline void fetchPacket(HTTP_PACKET *packet) { fetchPokemonResult(packet); }
static inline void sendPacket(PACKET *packet) { sendPokemonResult(packet); }
static inline u32 downloadPacket(HTTP_PACKET *packet);
static inline u32 uploadPacket(PACKET *packet);
static inline u32 handleAsync();

void handlePackets();
BOOL handlePacket(PACKET *packet);
BOOL handleDataPacket(DATA_PACKET *packet);
BOOL handleCodePacket(CODE_PACKET *packet);
BOOL handleDumpPacket(DUMP_PACKET *packet);
BOOL setPacketSizes();

#endif // _COMMUNICATION_H
