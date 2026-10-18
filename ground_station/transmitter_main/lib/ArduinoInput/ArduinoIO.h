#ifndef PAFIK_GROUND_ST_IO
#define PAFIK_GROUND_ST_IO

#ifdef ARDUINO

    #include <Arduino.h>
    #include <nRF24L01.h> 
    #include <RF24.h>    
    #include "Structs.h" 
    #include "../../Shared/CommProtocol.h"
    #define LED 2
    #define BUTTON_1 4
    #define BUTTON_2 5

    class Input {
        public:
            Input(Buffer& empty_buffer) : buffer(empty_buffer) {}
            Buffer& buffer;

            void scan_inputs() {
                if (digitalRead(BUTTON_1)==HIGH) {
                    Command cmd1 {Controller,Throttle,100};
                    Command cmd2 {Controller,Steering,0};
                    buffer.push(cmd1);
                    buffer.push(cmd2);
                }
                else if (digitalRead(BUTTON_2)==HIGH) {
                    Command cmd1 {Controller,Throttle,-100};
                    Command cmd2 {Controller,Steering,0};
                    buffer.push(cmd1);
                    buffer.push(cmd2);
                }
                
                // taką serię if-ów dodawać dla każdego osobnego źródła
            }   
    };

    class RadioSession {
        private:
        CurrentState& state;
        RF24& radio;
        uint16_t id = 0;

        public:
        RadioSession (CurrentState& state, RF24& radio): 
            state(state), radio(radio) {}

        void send() {
            if (id<UINT16_MAX) {id++;}
            else {id = 0;}

            uint8_t flags = 0;
            flags |= state.lights << 0;     // pierwszy z 8 bitów bajtu

            Packet packet {
                id,
                state.throttle, 
                state.steering,
                flags
            };
            radio.write(&packet, sizeof(packet));
        }
    };

#endif
#endif