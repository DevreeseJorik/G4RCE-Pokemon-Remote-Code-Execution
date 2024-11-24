#include "packet_handler.h"

#include "util/memory.h"

void handlePackets() {
    PACKET *rcvPacket = RCV_PACKET_BUFF_ADDRESS;

    u32 result;
    while (TRUE) {
        result = downloadPacket(rcvPacket, PACKET_COUNT);
        switch (result) {
            case 1:
            case PACKET_COUNT:
                if (!handlePacket(rcvPacket) || !rcvPacket->header.requestNext)
                    return;
            default:
                break;
        }
    }
}

static inline u32 downloadPacket(PACKET *packet, u32 packet_count) {
    fetchPacket(packet, packet_count);
    return handleAsync();
}

static inline u32 uploadPacket(PACKET *packet) {
    sendPacket(packet);
    return handleAsync();
}

static inline u32 handleAsync() {
    while (TRUE) {
        tryAsyncUpdate();
        if (isAsyncComplete())
            break;
    }
    return getAsyncResult();
}

BOOL handlePacket(PACKET *packet) {
    switch (packet->header.packetType){
        case TYPE_NONE:
            return FALSE;
        case TYPE_DATA_PACKET:
            return handleDataPacket((DATA_PACKET*)packet);
        case TYPE_CODE_PACKET:
            return handleCodePacket((CODE_PACKET*)packet);
        case TYPE_DUMP_PACKET:
            return handleDumpPacket((DUMP_PACKET*)packet);
        default:
            return FALSE;
    }
}

BOOL handleDataPacket(DATA_PACKET *packet) {
    if (packet->header.destinationAddress == NULL)
        return FALSE;

    memcp(packet->header.destinationAddress, packet->data, packet->header.size);
    return TRUE;
}

BOOL handleCodePacket(CODE_PACKET *packet) {
    return fp_thumb(packet->data, BOOL, ())();
}

BOOL handleDumpPacket(DUMP_PACKET *packet) {
    if (packet->header.dump_address == NULL)
        return FALSE;

    uploadPacket(packet->header.dump_address);
    return TRUE;
}
