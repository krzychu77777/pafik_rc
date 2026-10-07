#ifndef PAFIK_INPUTS
#define PAFIK_INPUTS

#include <Arduino.h>
#include "Structs.h"
#define LED 2
#define BUTTON_1 4
#define BUTTON_2 5

class Input {
    public:
        Input(Buffer& empty_buffer) : raw_buffer(empty_buffer) {}

        Buffer raw_buffer;

        void scan_inputs() {
            Command cmd;
            cmd.source = Undefined;

            if (digitalRead(BUTTON_1)==HIGH) {
                cmd.source = Controller;
                cmd.type = Movement;
                cmd.task = Forward;
                cmd.value = 100;
            }
            else if (digitalRead(BUTTON_2)==HIGH) {
                cmd.source = Controller;
                cmd.type = Movement;
                cmd.task = Backward;
                cmd.value = 100;
            }
            raw_buffer.push(cmd);
        }
    
    private:
        int it = 0;

};

#endif