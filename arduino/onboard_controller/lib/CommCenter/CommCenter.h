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
    SteeringMode& mode;

public:
    CommCenter(logBuff& logs, RF24& radio, ControlInbox& inbox, Vehicle& vehicle): 
    log_buffer(logs), radio(radio), inbox(inbox), pipe(vehicle.radio_pipe), mode(vehicle.mode) {}

    void update() {
        BackLog pending;

        // LOG ZWROTNY
        if (log_buffer.peek(pending)) {
            if (radio.writeAckPayload(pipe, &pending, sizeof(pending))) {
                if (mode == AUTO)  {
                    Serial.write(reinterpret_cast<const uint8_t*>(&pending), sizeof(pending));
                }
                log_buffer.pop(pending);        // <--- tylko po to żeby skasować log z bufora 
            }
        }

        // RADIO
        if (radio.available(&pipe)) {
            Packet incoming {0,0,0,0};
            radio.read(&incoming, sizeof(incoming));
            inbox.radio_msg = incoming;
        }

        // UART
        if (Serial.available() >= sizeof(Packet)) {
            Packet incoming {0,0,0,0};
            Serial.readBytes(reinterpret_cast<char*>(&incoming), sizeof(incoming));
            inbox.uart_msg = incoming;
        }        
        
    }
};

#endif