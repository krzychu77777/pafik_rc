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

struct BackLog {
public: 
    LogType type;
    LogCode code;

    //BackLog(LogType type, LogCode code): type(type), code(code) {}
};

static_assert(sizeof(Packet) == 8,
              "Unexpected ControlPacket size");

enum LogType: uint8_t {
    INFO,
    WARNING,
    ERROR,
    SETUP
};

enum LogCode: uint8_t {
    command_buffer_exceeded,
    log_queue_overflow,
    buffer_already_empty,
    no_priority_for_this_source,
    log_queue_already_empty,
    arbitrage_error,
    unknown_command,
    pinging,
    im_ready,
    OK
};

inline const char* logTypeToString(LogType level)
{
    switch (level)
    {
        case LogType::INFO: return "INFO";
        case LogType::WARNING: return "WARNING";
        case LogType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

inline const char* logCodeToString(LogCode level)
{
    switch (level)
    {
        case LogCode::command_buffer_exceeded: return "command_buffer_exceeded";
        case LogCode::arbitrage_error: return "arbitrage_error";
        case LogCode::unknown_command: return "unknown_command";
        case LogCode::log_queue_overflow: return "log_queue_overflow";
        case LogCode::log_queue_already_empty: return "log_queue_already_empty";
        case LogCode::im_ready: return "im_ready";
        case LogCode::OK: return "OK";
        default: return "UNKNOWN";
    }
}

#endif