#ifndef PAFIK_PROTOCOL
#define PAFIK_PROTOCOL

#include <stdint.h>

struct Packet {
    public:
        uint16_t packet_id;
        int16_t throttle;
        int16_t steering;
        uint8_t flags;
        uint8_t padding;        //puste miejsce bo niektóre środowiska zaokrąglają
                                // 7 bitów do 8 (padding)

    Packet (
        uint16_t packet_id,
        int16_t throttle,
        int16_t steering,
        uint8_t flags
    ):packet_id(packet_id), throttle(throttle), steering(steering), flags(flags) {}
};

static_assert(sizeof(Packet) == 8,
              "Unexpected ControlPacket size");

#endif