#ifndef PAFIK_LOGGER
#define PAFIK_LOGGER

#include "../../../Shared/CommProtocol.h"

#ifdef ARDUINO
    #include "SerialLogSink.h"
    using DefaultLogSink = SerialLogSink;
#else
    #include "ConsoleLogSink.h"
    using DefaultLogSink = ConsoleLogSink;
#endif

class Logger {
private:
    DefaultLogSink& sink;

public: 
    Logger(DefaultLogSink& sink) : sink(sink) {}

    void warning(LogCode code) {
        sink.write(WARNING, code);
    }

    void error(LogCode code) {
        sink.write(ERROR, code);
    }

    void info (LogCode code) {
        sink.write(INFO, code);
    }

    void car_response (BackLog& status) {
        sink.backlog(status.type, status.code);
    }

};

#endif