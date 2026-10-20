#ifndef ONBOARD_COMMCENTER
#define ONBOARD_COMMCENTER

#include <nRF24L01.h> 
#include <RF24.h>  

#include "Structs.h"
#include "../../../shared/CommProtocol.h"

class CommCenter {
private: 
    logBuff& log_buffer;
    RF24& radio;
public:
    CommCenter(logBuff& logs, RF24& radio): log_buffer(logs), radio(radio) {}

    void get_and_send() {
    if (radio.available()) {
        if (!log_buffer.empty()) {
            BackLog pending = log_buffer.pop();
        }
        Packet incoming {0,0,0,0};
        radio.read(&incoming, sizeof(incoming));
    }
    }
};

#endif