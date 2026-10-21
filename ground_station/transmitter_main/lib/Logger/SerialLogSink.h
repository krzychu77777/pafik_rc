#ifndef PAFIK_SERIAL_LOG_SINK
#define PAFIK_SERIAL_LOG_SINK

#include <Arduino.h>
#include "Structs.h"

class SerialLogSink 
{
public:
    void systemLog(LogType type, LogCode code) {
        Serial.print("[System:] ");
        Serial.print(logTypeToString(type));
        Serial.print(" | ");
        Serial.println(logCodeToString(code));
    }

    void backlog(LogType type, LogCode code) {
        Serial.print("[Pafik:]  ");
        Serial.print(logTypeToString(type));
        Serial.print(" | ");
        Serial.println(logCodeToString(code));
    }
};

#endif