#ifndef PAFIK_VEHICLE
#define PAFIK_VEHICLE

enum SteeringMode {AUTO,MANUAL};

class Vehicle {
public:
    SteeringMode mode;

    Vehicle() {
        mode = MANUAL;
    }
};

#endif