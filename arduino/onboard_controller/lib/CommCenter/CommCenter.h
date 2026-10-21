#ifndef ONBOARD_COMMCENTER
#define ONBOARD_COMMCENTER

#include <nRF24L01.h> 
#include <RF24.h>  

#include "Structs.h"
#include "../../../../shared/CommProtocol.h"

struct ControlInbox {
    Packet radio_msg {0,0,0,0};
    Packet uart_msg {0,0,0,0};
};

class CommCenter {
private: 
    logBuff& log_buffer;
    RF24& radio;
    ControlInbox& inbox;
    uint8_t &pipe;
public:
    CommCenter(logBuff& logs, RF24& radio, ControlInbox& inbox, uint8_t &pipe): 
    log_buffer(logs), radio(radio), inbox(inbox), pipe(pipe) {}

    void update() {
        BackLog pending;

        // RADIO
        if (log_buffer.pop(pending)) {
                radio.writeAckPayload(pipe, &pending, sizeof(pending));
            }
        if (radio.available(&pipe)) {
            Packet incoming {0,0,0,0};
            radio.read(&incoming, sizeof(incoming));
            inbox.radio_msg = incoming;
        }

        // UART                                                                             <----- DO POPRAWY
        if (Serial.available() >= sizeof(Packet)) {
            Packet incoming {0,0,0,0};
            Serial.readBytes(reinterpret_cast<char*>(&incoming), sizeof(incoming));
            inbox.uart_msg = incoming;
        }        
        Serial.write(reinterpret_cast<const uint8_t*>(&pending), sizeof(pending));
    }
};

#endif