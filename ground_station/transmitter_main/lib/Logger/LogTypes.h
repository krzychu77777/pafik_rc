#ifndef PAFIK_LOGTYPES
#define PAFIK_LOGTYPES

enum LogType {
    INFO,
    WARNING,
    ERROR
};

enum LogCode {
    buffer_exceeded,
    buffer_already_empty,
    no_priority_for_this_source,
    arbitrage_error,
    unknown_command,
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
        case LogCode::buffer_exceeded: return "buffer_exceeded";
        case LogCode::arbitrage_error: return "arbitrage_error";
        case LogCode::unknown_command: return "unknown_command";
        case LogCode::OK: return "OK";
        default: return "UNKNOWN";
    }
}

#endif