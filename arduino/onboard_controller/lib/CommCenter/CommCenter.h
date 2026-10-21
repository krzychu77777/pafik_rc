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
    uint8_t &pipe;
public:
    CommCenter(logBuff& logs, RF24& radio, uint8_t &pipe): 
    log_buffer(logs), radio(radio), pipe(pipe) {}

    void get_and_send() {
    if (radio.available(&pipe)) {
        BackLog pending;
        if (log_buffer.pop(pending)) {
            radio.writeAckPayload(pipe, &pending, sizeof(pending));
        }
        Packet incoming {0,0,0,0};
        radio.read(&incoming, sizeof(incoming));
    }
    }
};

#endif