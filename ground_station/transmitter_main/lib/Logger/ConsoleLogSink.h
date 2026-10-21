#ifndef PAFIK_CONSOLE_LOG_SINK
#define PAFIK_CONSOLE_LOG_SINK

#include "Structs.h"
#include <iostream>

class ConsoleLogSink
{
public:
    void systemLog(LogType type, LogCode code)
    {
        std::cout << "[System:] " 
                  << logTypeToString(type)
                  << " | "
                  << logCodeToString(code)
                  << std::endl;
    }

    void backlog(LogType type, LogCode code)
    {
        std::cout << "[Pafik:]  "
                  << logTypeToString(type)
                  << " | "
                  << logCodeToString(code)
                  << std::endl;
    }
};

#endif