#ifndef ONBOARD_LOGGER
#define ONBOARD_LOGGER

#include <nRF24L01.h> 
#include <RF24.h>  

enum LogType {
    INFO,
    WARNING,
    ERROR,
    SETUP
};

enum LogCode {
    buffer_exceeded,
    buffer_already_empty,
    no_priority_for_this_source,
    arbitrage_error,
    unknown_command,
    status_please,
    OK
};

struct BackLog {
public: 
    LogType type;
    LogCode code;

    BackLog(LogType type, LogCode code): type(type), code(code) {}
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
        case LogCode::buffer_exceeded: return "buffer_exceeded";
        case LogCode::arbitrage_error: return "arbitrage_error";
        case LogCode::unknown_command: return "unknown_command";
        case LogCode::OK: return "OK";
        default: return "UNKNOWN";
    }
}

class Sink {
private:
    Vehicle& vehicle;
    RF24& radio;

public:
    Sink(Vehicle& vehicle, RF24& radio): vehicle(vehicle), radio(radio) {}

    void log(LogType type, LogCode code) {
        if (vehicle.mode == AUTO) {
            Serial.print("[Pafik:] ");
            Serial.print(logTypeToString(type));
            Serial.print(" | ");
            Serial.println(logCodeToString(code));
        }
        BackLog packet {type, code};
        radio.write(&packet, sizeof(packet));
    }
};


class Logger {
private:
    Sink& sink;
public:
    Logger(Sink& sink): sink(sink) {}

    void warning(LogCode code) {
        sink.log(WARNING, code);
    }

    void error(LogCode code) {
        sink.log(ERROR, code);
    }

    void info (LogCode code) {
        sink.log(INFO, code);
    }
};


#endif 