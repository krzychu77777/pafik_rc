#ifndef PAFIK_LOGGER
#define PAFIK_LOGGER

#include "Structs.h"

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

};

#endif