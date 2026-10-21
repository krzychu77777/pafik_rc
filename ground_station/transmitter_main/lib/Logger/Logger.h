#ifndef PAFIK_LOGGER
#define PAFIK_LOGGER

#include "../../../../shared/CommProtocol.h"

#ifdef ARDUINO
    #include "SerialLogSink.h"
    using DefaultLogSink = SerialLogSink;
#else
    #include "ConsoleLogSink.h"
    using DefaultLogSink = ConsoleLogSink;
#endif

enum Author {System, Pafik};    // to się przyda 
                                // gdy będziemy wysyłać 
                                // binarne logi do apki
                                // 
struct UserLog {                // wtedy trzeba to      
    Author author;              // przenieść do kodu
    LogType type;               // odpowiedniego, nowego
    LogCode code;               // sinku
};


class Logger {
private:
    DefaultLogSink& sink;

public: 
    Logger(DefaultLogSink& sink) : sink(sink) {}

    void warning(LogCode code) {
        sink.systemLog(WARNING, code);
    }

    void error(LogCode code) {
        sink.systemLog(ERROR, code);
    }

    void info (LogCode code) {
        sink.systemLog(INFO, code);
    }

    void car_response (BackLog& status) {
        sink.backlog(status.type, status.code);
    }

};

#endif