#ifndef PAFIK_VEHICLE
#define PAFIK_VEHICLE

enum SteeringMode {AUTO,MANUAL};

class Vehicle {
public:
    SteeringMode mode;
    uint8_t radio_pipe = 0;

    Vehicle() {
        mode = MANUAL;        
    }
};

#endif