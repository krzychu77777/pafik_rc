#ifndef ONBOARD_LOGGER
#define ONBOARD_LOGGER

#include <nRF24L01.h> 
#include <RF24.h>  

#include "../../../shared/CommProtocol.h"
#include "Structs.h"

class Sink {
private:
    Vehicle& vehicle;
    logBuff& log_buffer;

public:
    Sink(Vehicle& vehicle, logBuff& log_buffer):
         vehicle(vehicle), log_buffer(log_buffer) {}

    void log(LogType type, LogCode code) {
        if (vehicle.mode == AUTO) {
            Serial.print("[Pafik:] ");
            Serial.print(logTypeToString(type));
            Serial.print(" | ");
            Serial.println(logCodeToString(code));
        }
        BackLog packet {type, code};
        log_buffer.push(packet);
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