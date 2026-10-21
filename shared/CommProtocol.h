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
    ):packet_id(packet_id), throttle(throttle), steering(steering), flags(flags), padding(0) {}
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
    // komendy stacji naziemnej 
    //===========================
    pinging,            //info
    radio_detected,
    connection_with_Pafik_estabilished,
    setup_done,

    unknown_command,    // warning
    buffer_already_empty,
    no_priority_for_this_source,
    waiting_for_pafik_response,

    command_buffer_exceeded,    //err
    radio_not_detected,
    arbitrage_error,
    
    // komendy pojazdu
    //============================
    im_ready,
    OK
};

struct BackLog {
public: 
    LogType type;
    LogCode code;

    //BackLog(LogType type, LogCode code): type(type), code(code) {}
};

inline const char* logTypeToString(LogType level)
{
    switch (level)
    {
        case LogType::INFO: return "INFO";
        case LogType::WARNING: return "WARNING";
        case LogType::ERROR: return "ERROR";
        case LogType::SETUP: return "SETUP";
        default: return "UNKNOWN";
    }
}

inline const char* logCodeToString(LogCode level)
{
    switch (level)
    {
        // komendy stacji naziemnej
        case LogCode::pinging:
            return "pinging";
        case LogCode::radio_detected:
            return "radio_detected";
        case LogCode::connection_with_Pafik_estabilished:
            return "connection_with_Pafik_estabilished";
        case LogCode::setup_done:
            return "setup_done";

        case LogCode::unknown_command:
            return "unknown_command";
        case LogCode::buffer_already_empty:
            return "buffer_already_empty";
        case LogCode::no_priority_for_this_source:
            return "no_priority_for_this_source";
        case LogCode::waiting_for_pafik_response:
            return "waiting_for_pafik_response";

        case LogCode::command_buffer_exceeded:
            return "command_buffer_exceeded";
        case LogCode::radio_not_detected:
            return "radio_not_detected";
        case LogCode::arbitrage_error:
            return "arbitrage_error";

        // komendy pojazdu
        case LogCode::im_ready:
            return "im_ready";
        case LogCode::OK:
            return "OK";

        default:
            return "UNKNOWN";
    }
}

#endif