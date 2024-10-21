#ifndef _PACKETS_H
#define _PACKETS_H

#include "util/types.h"

#define PACKET_SIZE 292
#define CUSTOM_PACKET_SIZE 3000

enum {
    TYPE_NONE,
    TYPE_DATA_PACKET,    // copy to some destination
    TYPE_CODE_PACKET,    // execute on receive
	TYPE_DUMP_PACKET,    // dump data
};

typedef struct {
    u8 packetType;
	u8 requestNext;
	u16 padding;
    u32 packetId;
} PACKET_HEADER;

typedef struct {
    PACKET_HEADER header;
    u8 data[ PACKET_SIZE - sizeof(PACKET_HEADER)];
} PACKET;

typedef struct {
	u8 http_header[0xD4];
	PACKET packet;
} HTTP_PACKET;

typedef struct {
    PACKET_HEADER header;
    void *destinationAddress;
    u32 size;
} DATA_PACKET_HEADER;

typedef struct {
    DATA_PACKET_HEADER header;
    u8 data[ PACKET_SIZE - sizeof(DATA_PACKET_HEADER)];
} DATA_PACKET;

typedef struct {
    PACKET_HEADER header;
} CODE_PACKET_HEADER;

typedef struct {
    CODE_PACKET_HEADER header;
    u8 data[ PACKET_SIZE - sizeof(CODE_PACKET_HEADER)];
} CODE_PACKET;

typedef struct {
	PACKET_HEADER header;
	void *dump_address;
	u32 dump_size;
} DUMP_PACKET_HEADER;

typedef struct {
	DUMP_PACKET_HEADER header;
	u8 data[PACKET_SIZE - sizeof(DUMP_PACKET_HEADER)];
} DUMP_PACKET;

#endif // _PACKETS_H
