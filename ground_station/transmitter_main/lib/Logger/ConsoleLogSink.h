#ifndef PAFIK_CONSOLE_LOG_SINK
#define PAFIK_CONSOLE_LOG_SINK

#include "Structs.h"
#include <iostream>

class ConsoleLogSink
{
public:
    void write(LogType type, LogCode code)
    {
        std::cout << logTypeToString(type)
                  << " | "
                  << logCodeToString(code)
                  << std::endl;
    }
};

#endif