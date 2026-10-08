#ifndef PAFIK_SERIAL_LOG_SINK
#define PAFIK_SERIAL_LOG_SINK

#include <Arduino.h>
#include "Structs.h"

class SerialLogSink 
{
public:
    void write(LogType type, LogCode code) {
        Serial.print(logTypeToString(type));
        Serial.print(" | ");
        Serial.println(logCodeToString(code));
    }
};

#endif